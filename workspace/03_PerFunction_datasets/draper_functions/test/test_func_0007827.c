ecore_file_readlink(const char *lnk)
{
   char buf[PATH_MAX];
   int count;

   if ((count = readlink(lnk, buf, sizeof(buf) - 1)) < 0) return NULL;
   buf[count] = 0;
   return strdup(buf);
}
