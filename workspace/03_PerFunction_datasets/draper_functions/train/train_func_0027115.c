cdindex_stat_disc_data(int cd_desc, struct cddb_entry *entry)
{
   struct disc_info disc;
   struct stat st;
   char root_dir[256], file[256];

   if(getenv("HOME") == NULL) {
      strncpy(cddb_message, "$HOME is not set!", 256);
      return -1;
   }

   if(cd_stat(cd_desc, &disc) < 0)
     return -1;

   entry->entry_id = __internal_cddb_discid(disc);

   if(__internal_cdindex_discid(disc, entry->entry_cdindex_id,
				CDINDEX_ID_SIZE) < 0)
     return -1;

   snprintf(root_dir, 256, "%s/.cdindex", getenv("HOME"));


   if(stat(root_dir, &st) < 0) {
      if(errno != ENOENT)
        return -1;
      else {
         entry->entry_present = 0;
         return 0;
      }
   } else {
      if(!S_ISDIR(st.st_mode)) {
         errno = ENOTDIR;
         return -1;
      }
   }

   snprintf(file, 256, "%s/%s", root_dir, entry->entry_cdindex_id);
   if(stat(file, &st) == 0) {
      entry->entry_timestamp = st.st_mtime;
      entry->entry_present = 1;
      entry->entry_genre = CDDB_MISC;

      return 0;
   }

   entry->entry_present = 0;

   return 0;
}
