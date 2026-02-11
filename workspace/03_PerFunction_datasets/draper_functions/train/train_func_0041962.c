_check_item(const Evry_Item *it)
{
   char *suffix;

   GET_FILE(file, it);

   if (!evry_file_path_get(file) || !file->mime) return 0;

   if (!strncmp(file->mime, "image/", 6))
     return 1;

   if ((suffix = strrchr(it->label, '.')))
     if (!strncmp(suffix, ".edj", 4))
       return 1;

   return 0;
}
