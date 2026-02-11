writerc ()
{
  FILE *fp;
  char *pcomm[4] = { "lpr\\-P", "lp\\-d", "kprinter -d","gtklp -d"};
  char *ori[2] = { "portrait", "landscape" };
  char *epso[4] = { "None","EPSI","TIFFm","TIFFc" };
  gchar *filename;

  filename = g_malloc (PATH_MAX + 1);
  filename =
    strncat (strncpy (filename, g_get_home_dir (), PATH_MAX), "/.chemtoolrc",
	     PATH_MAX);
  fp = fopen (filename, "w");
  if (!fp)
    {
      g_free (filename);
      return 1;
    }
  else
    {
      fprintf (fp, "datadir %s\n", datadir);
      fprintf (fp, "extension %s\n", datamask);
      fprintf (fp, "papersize %s\n", paper[papersize]);
      fprintf (fp, "orientation %s\n", ori[orient]);
      fprintf (fp, "printscale %f\n", printscale);
      fprintf (fp, "printcommand %s\n", pcomm[printcmd]);
      fprintf (fp, "printer %s\n", queuename);
      fprintf (fp, "bondlength %6.4f\n", bondlen_mm);
      fprintf (fp, "double_separation %d\n", db_dist);
      fprintf (fp, "epsoption %s\n", epso[epsoption]);
      fprintf (fp, "whiteout %d\n", use_whiteout);
      fprintf (fp, "intlchars %d\n", use_intlchars);
      fprintf (fp, "background (%d,%d,%d)\n", bgred,bggreen,bgblue);
      fclose (fp);
      g_free (filename);
      return 0;
    }
}
