ecore_file_recursive_rm(const char *dir)
{
   Eina_Iterator *it;
   char buf[PATH_MAX];
   struct stat st;
   int ret;

   if (readlink(dir, buf, sizeof(buf) - 1) > 0)
     return ecore_file_unlink(dir);

   ret = stat(dir, &st);
   if ((ret == 0) && (S_ISDIR(st.st_mode)))
     {
        Eina_File_Direct_Info *info;

        ret = 1;
        if (stat(dir, &st) == -1) return EINA_FALSE;

        it = eina_file_direct_ls(dir);
        EINA_ITERATOR_FOREACH(it, info)
          {
             if (!ecore_file_recursive_rm(info->path))
               ret = 0;
          }
        eina_iterator_free(it);

        if (!ecore_file_rmdir(dir)) ret = 0;
        if (ret)
            return EINA_TRUE;
        else
            return EINA_FALSE;
     }
   else
     {
        if (ret == -1) return EINA_FALSE;
        return ecore_file_unlink(dir);
     }
}
