split_packets (const char *fname)
{
  FILE *fp;
  int rc;

  if (!fname || !strcmp (fname, "-"))
    {
      fp = stdin;
      fname = "-";
    }
  else if ( !(fp = fopen (fname,"rb")) )
    {
      log_error ("can't open `%s': %s\n", fname, strerror (errno));
      return;
    }

  while ( !(rc = do_split (fname, fp)) )
    ;
  if ( rc > 0 )
    ;
  else if ( ferror (fp) )
    log_error ("error reading `%s': %s\n", fname, strerror (errno));
  else
    log_error ("premature EOF while reading `%s'\n", fname );

  if ( fp != stdin )
    fclose (fp);
}
