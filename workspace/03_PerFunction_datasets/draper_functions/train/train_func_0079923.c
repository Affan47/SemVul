receive_data (FILE * instr, FILE * outstr, off_t blksize)
{
  int c;
  int cnt, bare_lfs = 0;
  char *buf;

  transflag++;
  if (setjmp (urgcatch))
    {
      transflag = 0;
      return -1;
    }
  switch (type)
    {
    case TYPE_I:
    case TYPE_L:
      buf = malloc ((u_int) blksize);
      if (buf == NULL)
	{
	  transflag = 0;
	  perror_reply (451, "Local resource failure: malloc");
	  return -1;
	}

      while ((cnt = read (fileno (instr), buf, blksize)) > 0)
	{
	  if (write (fileno (outstr), buf, cnt) != cnt)
	    {
	      free (buf);
	      goto file_err;
	    }
	  byte_count += cnt;
	}
      free (buf);
      if (cnt < 0)
	goto data_err;
      transflag = 0;
      return 0;

    case TYPE_E:
      reply (553, "TYPE E not implemented.");
      transflag = 0;
      return -1;

    case TYPE_A:
      while ((c = getc (instr)) != EOF)
	{
	  byte_count++;
	  if (c == '\n')
	    bare_lfs++;
	  while (c == '\r')
	    {
	      if (ferror (outstr))
		goto data_err;
	      c = getc (instr);
	      if (c != '\n')
		{
		  putc ('\r', outstr);
		  if (c == '\0' || c == EOF)
		    goto contin2;
		}
	    }
	  putc (c, outstr);
	contin2:;
	}
      fflush (outstr);
      if (ferror (instr))
	goto data_err;
      if (ferror (outstr))
	goto file_err;
      transflag = 0;
      if (bare_lfs)
	{
	  lreply (226, "WARNING! %d bare linefeeds received in ASCII mode",
		  bare_lfs);
	  printf ("   File may not have transferred correctly.\r\n");
	}
      return (0);
    default:
      reply (550, "Unimplemented TYPE %d in receive_data", type);
      transflag = 0;
      return -1;
    }

data_err:
  transflag = 0;
  perror_reply (426, "Data Connection");
  return -1;

file_err:
  transflag = 0;
  perror_reply (452, "Error writing file");
  return -1;
}
