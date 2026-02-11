remove_tmpfile(void)
{
   if (tempfile_fd > 0)
      close(tempfile_fd);
   if (tempfile != NULL) {
      unlink(tempfile);
      free(tempfile);
   }
}
