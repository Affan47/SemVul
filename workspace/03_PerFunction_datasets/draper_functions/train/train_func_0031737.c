flush_output_files (void)
{
  struct file_section *fs;
  for (fs = file_array; fs->fpp; fs ++) {
    if (ferror(*(fs->fpp))) {
      fprintf (stderr, "%s: write error\n", progname);
      exit (1);
    }
  }
  for (fs = file_array; fs->fpp; fs ++) {
    if (fflush(*(fs->fpp))) {
      fprintf (stderr, "%s: write error: %s\n", progname, strerror (errno));
      exit (1);
    }
  }
}
