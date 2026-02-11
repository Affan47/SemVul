_e_fm_ipc_cb_fop_trash_idler(void *data)
{
   E_Fop *fop = NULL;
   FILE *info = NULL;
   const char *filename;
   const char *escname = NULL;
   char *dest, *trash_dir;
   char buf[4096];
   unsigned int i = 0;
   struct tm *lt;
   time_t t;


   fop = (E_Fop *)data;
   if (!fop) return 0;


   snprintf(buf, sizeof(buf), "%s/Trash", efreet_data_home_get());
   trash_dir = strdupa(buf);
   snprintf(buf, sizeof(buf), "%s/files", trash_dir);
   if (!ecore_file_mkpath(buf)) return 0;
   snprintf(buf, sizeof(buf), "%s/info", trash_dir);
   if (!ecore_file_mkpath(buf)) return 0;

   filename = strrchr(fop->src, '/');
   if (!filename) return 0;
   escname = ecore_file_escape_name(filename);


   do
     {
        snprintf(buf, sizeof(buf), "%s/file%s.%p.%u", trash_dir, escname,
                 fop, i++);
     }
   while (ecore_file_exists(buf));
   dest = strdup(buf);


   if (rename(fop->src, dest))
     {
        if (errno == EXDEV)
          {

             free(dest);
             ecore_file_unlink(fop->src);
             return ECORE_CALLBACK_CANCEL;
          }
     }


   snprintf(buf, sizeof(buf), "%s/info%s.%p.%u.trashinfo", trash_dir,
            escname, fop, --i);
   info = fopen(buf, "w");
   if (info)
     {
        t = time(NULL);
        lt = localtime(&t);


        fprintf(info,
                "[Trash Info]\nPath=%s\nDeletionDate=%04u%02u%02uT%02u:%02u:%02u",
                fop->src, lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
                lt->tm_hour, lt->tm_min, lt->tm_sec);
        fclose(info);
     }
   else

     rename(dest, fop->src);

   free(dest);
   eina_stringshare_del(fop->src);
   eina_stringshare_del(fop->dst);
   _e_fops = eina_list_remove(_e_fops, fop);
   free(fop);
   return ECORE_CALLBACK_CANCEL;
}
