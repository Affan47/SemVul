backup_create_md5_file(const char *filename)
{
   UINT8 dig[16];
   MD5   md5;
   FILE  *thefile;
   UINT8 buf[4096];
   INT32 len;
   char  newpath[1024];

   md5.Init();

   thefile = fopen(filename, "rb");
   if (thefile == NULL)
   {
      LOG_FMT(LERR, "%s: fopen(%s) failed: %s (%d)\n",
              __func__, filename, strerror(errno), errno);
      return;
   }

   while ((len = fread(buf, 1, sizeof(buf), thefile)) > 0)
   {
      md5.Update(buf, len);
   }

   fclose(thefile);
   md5.Final(dig);

   snprintf(newpath, sizeof(newpath), "%s%s", filename, UNC_BACKUP_MD5_SUFFIX);

   thefile = fopen(newpath, "wb");
   if (thefile != NULL)
   {
      fprintf(thefile,
              "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x  %s\n",
              dig[0], dig[1], dig[2], dig[3],
              dig[4], dig[5], dig[6], dig[7],
              dig[8], dig[9], dig[10], dig[11],
              dig[12], dig[13], dig[14], dig[15],
              path_basename(filename));

      fclose(thefile);
   }
}
