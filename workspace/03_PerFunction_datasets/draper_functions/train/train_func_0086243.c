dump_fonts (FILE * stream, struct a2ps_job * job)
{
  FILE * fp;
  char * filename;
  const char * fontname;
  char ** fonts;
  int i;


  fonts = required_fonts_get (job);
  if (!fonts)
    return;

  for (i = 0 ; fonts [i] ; i++)
    {

      fontname = fonts_map_resolve_alias (job->fonts_map, fonts [i]);


      filename = pw_find_file (job->common.path, fontname, ".pfb");
      if (!filename)
	filename = pw_find_file (job->common.path, fontname, ".pfa");
      if (!filename)
	filename = pw_find_file (job->common.path, fontname, ".gsf");
      if (!filename)
	{


	  char * file;
	  astrcat2 (file, fontname, ".pfb");
	  error (0, 0, _("cannot find file `%s'"), quotearg (file));
	  strcat2 (file, fontname, ".pfa");
	  error (0, 0, _("cannot find file `%s'"), quotearg (file));
	  strcat2 (file, fontname, ".gsf");
	  error (1, 0, _("cannot find file `%s'"), quotearg (file));
	}


      fp = xrfopen (filename);


      message (msg_font | msg_file, (stderr, "Dumping file `%s'\n", filename));
      fprintf (stream, "%%%%BeginResource: font %s\n", fonts [i]);
      if (!internal_font_file_dump (fp, stream))
	error (1, 0, "Bad PostScript font file `%s'\n", filename);
      fprintf (stream, "%%%%EndResource\n");


      fclose (fp);
      free (filename);
    }
  free (fonts);
}
