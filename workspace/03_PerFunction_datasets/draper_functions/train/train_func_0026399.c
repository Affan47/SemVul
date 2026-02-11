close_output_file (void)
{
  if (output_stream)
    {
      if (ferror (output_stream))
        {
          error (0, 0, _("write error for %s"), quote (output_filename));
          output_stream = NULL;
          cleanup_fatal ();
        }
      if (fclose (output_stream) != 0)
        {
          error (0, errno, "%s", output_filename);
          output_stream = NULL;
          cleanup_fatal ();
        }
      if (bytes_written == 0 && elide_empty_files)
        {
          sigset_t oldset;
          bool unlink_ok;
          int unlink_errno;


          sigprocmask (SIG_BLOCK, &caught_signals, &oldset);
          unlink_ok = (unlink (output_filename) == 0);
          unlink_errno = errno;
          files_created -= unlink_ok;
          sigprocmask (SIG_SETMASK, &oldset, NULL);

          if (! unlink_ok)
            error (0, unlink_errno, "%s", output_filename);
        }
      else
        {
          if (!suppress_count)
            {
              char buf[INT_BUFSIZE_BOUND (uintmax_t)];
              fprintf (stdout, "%s\n", umaxtostr (bytes_written, buf));
            }
        }
      output_stream = NULL;
    }
}
