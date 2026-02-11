create_directories (void)
{
  struct stat statbuf;
  const char *defhome = standard_homedir ();
  char *home;

  home = make_filename (opt.homedir, NULL);
  if ( stat (home, &statbuf) )
    {
      if (errno == ENOENT)
        {
          if (
#ifdef HAVE_W32_SYSTEM
              ( !compare_filenames (home, defhome) )
#else
              (*defhome == '~'
                && (strlen (home) >= strlen (defhome+1)
                    && !strcmp (home + strlen(home)
                                - strlen (defhome+1), defhome+1)))
               || (*defhome != '~' && !strcmp (home, defhome) )
#endif
               )
            {
#ifdef HAVE_W32_SYSTEM
              if (!CreateDirectory (home, NULL))
                log_error (_("can't create directory `%s': %s\n"),
                           home, w32_strerror (-1) );
#else
              if (mkdir (home, S_IRUSR|S_IWUSR|S_IXUSR ))
                log_error (_("can't create directory `%s': %s\n"),
                           home, strerror (errno) );
#endif
              else
                {
                  if (!opt.quiet)
                    log_info (_("directory `%s' created\n"), home);
                  create_private_keys_directory (home);
                }
            }
        }
      else
        log_error (_("stat() failed for `%s': %s\n"), home, strerror (errno));
    }
  else if ( !S_ISDIR(statbuf.st_mode))
    {
      log_error (_("can't use `%s' as home directory\n"), home);
    }
  else
    {
      create_private_keys_directory (home);
    }
  xfree (home);
}
