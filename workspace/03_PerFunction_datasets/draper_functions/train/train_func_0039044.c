write_file_footers (structfile, externfile)
     FILE *structfile, *externfile;
{
  register int i;


  if (structfile)
    {
      for (i = 0; structfile_footer[i]; i++)
	fprintf (structfile, "%s\n", structfile_footer[i]);
    }
}
