ecore_file_exists(const char *file)
{
   struct stat st;
   if (!file) return EINA_FALSE;


   if (stat(file, &st) < 0 && strcmp(file, "/")) return EINA_FALSE;
   return EINA_TRUE;
}
