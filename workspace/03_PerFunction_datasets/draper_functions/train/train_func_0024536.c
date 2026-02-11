_ecore_file_mkpath_if_not_exists(const char *path)
{
   struct stat st;


#ifdef _WIN32
   if ((strlen(path) == 2) &&
       ((path[0] >= 'a' && path[0] <= 'z') ||
        (path[0] >= 'A' && path[0] <= 'Z')) &&
       (path[1] == ':'))
     return EINA_TRUE;
#endif

   if (stat(path, &st) < 0)
     return ecore_file_mkdir(path);
   else if (!S_ISDIR(st.st_mode))
     return EINA_FALSE;
   else
     return EINA_TRUE;
}
