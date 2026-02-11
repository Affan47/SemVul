make_file(UPSINFO *ups, const char *path)
{
   int makefd;

   if ((makefd = open(path, O_CREAT | O_WRONLY, 0644)) >= 0) {
      close(makefd);
   } else {
      log_event(ups, LOG_ERR, "Unable to create %s: ERR=%s\n",
         path, strerror(errno));
   }

   return makefd;
}
