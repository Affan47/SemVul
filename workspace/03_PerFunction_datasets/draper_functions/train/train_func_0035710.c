export_png_pic (char *filename, float scale)


{
  char com[255];
  FILE *xfile;
  int rval;
  char intl[3];

#ifdef GTK2
  setlocale (LC_NUMERIC,"C");
#endif

  if (figversion == 0)
    return (1);

  if (use_intlchars)
     strcpy(intl,"-j");
  else
     strcpy(intl,"");

  if ((int)strlen (filename))
    {
      if (figversion == 1)
	snprintf (com,255, "fig2dev %s -Lpng -m %f > \"%s\"", intl, scale, filename);
      else if (figversion == 2)
	snprintf (com,255, "fig2dev %s -L png -S 4 -F -m %f > \"%s\"", intl, scale, filename);
      else
	snprintf (com,255, "fig2dev %s -L png -g \\%s -S 4 -F -m %f > \"%s\"", intl, bghexcolor, scale, filename);
      xfile = popen (com, "w");
      if (!xfile)
	return (1);
      rval = exfig (xfile, 0);
      if (rval != 0)
        return (rval);
      rval=pclose(xfile);
      if (rval != 0)
	return (1);
      else
        return (rval);
    }
  else
    return (1);
}
