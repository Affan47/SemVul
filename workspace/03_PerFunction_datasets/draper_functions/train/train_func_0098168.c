ensure_dirfile_exists (char *dirfile)
{
  int desc;

  if (chicken_flag)
    return;

  desc = open (dirfile, O_RDONLY);
  if (desc < 0 && errno == ENOENT)
    {
      FILE *f;
      char *readerr = strerror (errno);
      close (desc);
      f = fopen (dirfile, "w");
      if (f)
        {
          fprintf (f, _("This is the file .../info/dir, which contains the\n\
topmost node of the Info hierarchy, called (dir)Top.\n\
The first time you invoke Info you start off looking at this node.\n\
%c\n\
%s\tThis is the top of the INFO tree\n\
\n\
  This (the Directory node) gives a menu of major topics.\n\
  Typing \"q\" exits, \"?\" lists all Info commands, \"d\" returns here,\n\
  \"h\" gives a primer for first-timers,\n\
  \"mEmacs<Return>\" visits the Emacs manual, etc.\n\
\n\
  In Emacs, you can click mouse button 2 on a menu item or cross reference\n\
  to select it.\n\
\n\
%s\n\
"),
            '\x1f',  "File: dir,\tNode: Top",  "* Menu:"
          );
          if (fclose (f) < 0)
            pfatal_with_name (dirfile);
        }
      else
        {

	  fatal (_("%s: could not read (%s) and could not create (%s)"),
		 dirfile, readerr, strerror (errno));
        }
    }
  else
    close (desc);
}
