export_babel (char *filename)


{
  char com[255];
  FILE *xfile;
  int rval;

  if ((int)strlen (filename))
    {
      snprintf (com,255, "babel -h -imol %s -o%s \"%s\"", babeloutp, babel, filename);
      xfile = popen (com, "w");
      if (!xfile)
	return (1);
      rval = export_mdl_mol (xfile, 1);
      if (pclose (xfile) < 0)
	return (1);
      return (rval);
    }
  else
    return (1);
}
