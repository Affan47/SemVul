fstype(const char *fname, char *fs, int fslen)
{
   struct stat st;
   mntent_cache_entry_t *mce;

   if (lstat(fname, &st) == 0) {
      if ((mce = find_mntent_mapping(st.st_dev)) != NULL) {
         bstrncpy(fs, mce->fstype, fslen);
         return true;
      }
      return false;
   }

   Dmsg1(50, "lstat() failed for \"%s\"\n", fname);
   return false;
}
