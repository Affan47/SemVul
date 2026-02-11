print_banner (saver_info *si)
{
  saver_preferences *p = &si->prefs;

  char *s, year[5];
  s = strchr (screensaver_id, '-');
  s = strrchr (s, '-');
  s++;
  strncpy (year, s, 4);
  year[4] = 0;


  p->verbose_p = (p->debug_p ||
                  get_boolean_resource (si->dpy, "verbose", "Boolean"));


  p->lock_p = get_boolean_resource (si->dpy, "lock", "Boolean");

  if (p->verbose_p)
    fprintf (stderr,
	     "%s %s, copyright (c) 1991-%s "
	     "by Jamie Zawinski <jwz@jwz.org>.\n",
	     progname, si->version, year);

  if (p->debug_p)
    fprintf (stderr, "\n"
	     "%s: Warning: running in DEBUG MODE.  Be afraid.\n"
	     "\n"
	     "\tNote that in debug mode, the xscreensaver window will only\n"
	     "\tcover the left half of the screen.  (The idea is that you\n"
	     "\tcan still see debugging output in a shell, if you position\n"
	     "\tit on the right side of the screen.)\n"
	     "\n"
	     "\tDebug mode is NOT SECURE.  Do not run with -debug in\n"
	     "\tuntrusted environments.\n"
	     "\n",
	     blurb());

  if (p->verbose_p && senescent_p ())
    fprintf (stderr, "\n"
             "*************************************"
             "**************************************\n"
	     "%s: Warning: this version of xscreensaver is VERY OLD!\n"
	     "%s: Please upgrade!  http://www.jwz.org/xscreensaver/\n"
             "*************************************"
             "**************************************\n"
	     "\n",
             blurb(), blurb());

  if (p->verbose_p)
    {
      if (!si->uid_message || !*si->uid_message)
	describe_uids (si, stderr);
      else
	{
	  if (si->orig_uid && *si->orig_uid)
	    fprintf (stderr, "%s: initial effective uid/gid was %s.\n",
		     blurb(), si->orig_uid);
	  fprintf (stderr, "%s: %s\n", blurb(), si->uid_message);
	}

      fprintf (stderr, "%s: in process %lu.\n", blurb(),
	       (unsigned long) getpid());
    }
}
