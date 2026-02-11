pdb_file_write_app_block(char *DB_name, void *bufp, size_t size_in)
{
   char local_pdb_file[FILENAME_MAX];
   char full_local_pdb_file[FILENAME_MAX];
   char full_local_pdb_file2[FILENAME_MAX];
   struct pi_file *pf1, *pf2;
   struct DBInfo infop;
   void *app_info;
   void *sort_info;
   void *record;
   int r;
   int idx;
   size_t size;
   int attr;
   int cat;
   pi_uid_t uid;
   struct stat statb;
   struct utimbuf times;

   jp_logf(JP_LOG_DEBUG, "pdb_file_write_app_block\n");

   g_snprintf(local_pdb_file, sizeof(local_pdb_file), "%s.pdb", DB_name);
   get_home_file_name(local_pdb_file, full_local_pdb_file, sizeof(full_local_pdb_file));
   strcpy(full_local_pdb_file2, full_local_pdb_file);
   strcat(full_local_pdb_file2, "2");


   stat(full_local_pdb_file, &statb);
   times.actime = statb.st_atime;
   times.modtime = statb.st_mtime;

   pf1 = pi_file_open(full_local_pdb_file);
   if (!pf1) {
      jp_logf(JP_LOG_WARN, _("Unable to open file: %s\n"), full_local_pdb_file);
      return EXIT_FAILURE;
   }
   pi_file_get_info(pf1, &infop);
   pf2 = pi_file_create(full_local_pdb_file2, &infop);
   if (!pf2) {
      jp_logf(JP_LOG_WARN, _("Unable to open file: %s\n"), full_local_pdb_file2);
      return EXIT_FAILURE;
   }

   pi_file_get_app_info(pf1, &app_info, &size);
   pi_file_set_app_info(pf2, bufp, size_in);

   pi_file_get_sort_info(pf1, &sort_info, &size);
   pi_file_set_sort_info(pf2, sort_info, size);

   for(idx=0;;idx++) {
      r = pi_file_read_record(pf1, idx, &record, &size, &attr, &cat, &uid);
      if (r<0) break;
      pi_file_append_record(pf2, record, size, attr, cat, uid);
   }

   pi_file_close(pf1);
   pi_file_close(pf2);

   if (rename(full_local_pdb_file2, full_local_pdb_file) < 0) {
      jp_logf(JP_LOG_WARN, "pdb_file_write_app_block(): %s\n", _("rename failed"));
   }

   utime(full_local_pdb_file, &times);

   return EXIT_SUCCESS;
}
