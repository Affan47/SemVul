sanei_genesys_write_pnm_file (char *filename, uint8_t * data, int depth,
			      int channels, int pixels_per_line, int lines)
{
  FILE *out;
  int count;

  DBG (DBG_info,
       "sanei_genesys_write_pnm_file: depth=%d, channels=%d, ppl=%d, lines=%d\n",
       depth, channels, pixels_per_line, lines);

  out = fopen (filename, "w");
  if (!out)
    {
      DBG (DBG_error,
	   "sanei_genesys_write_pnm_file: could nor open %s for writing: %s\n",
	   filename, strerror (errno));
      return SANE_STATUS_INVAL;
    }
  if(depth==1)
    {
      fprintf (out, "P4\n%d\n%d\n", pixels_per_line, lines);
    }
  else
    {
      fprintf (out, "P%c\n%d\n%d\n%d\n", channels == 1 ? '5' : '6',
	   pixels_per_line, lines, (int) pow (2, depth) - 1);
    }
  if (channels == 3)
    {
      for (count = 0; count < (pixels_per_line * lines * 3); count++)
	{
	  if (depth == 16)
	    fputc (*(data + 1), out);
	  fputc (*(data++), out);
	  if (depth == 16)
	    data++;
	}
    }
  else
    {
      if (depth==1)
        {
          pixels_per_line/=8;
        }
      for (count = 0; count < (pixels_per_line * lines); count++)
	{
          switch (depth)
            {
              case 8:
	        fputc (*(data + count), out);
                break;
              case 16:
	        fputc (*(data + 1), out);
	        fputc (*(data), out);
	        data += 2;
                break;
              default:
                fputc(data[count], out);
                break;
            }
	}
    }
  fclose (out);

  DBG (DBG_proc, "sanei_genesys_write_pnm_file: finished\n");
  return SANE_STATUS_GOOD;
}
