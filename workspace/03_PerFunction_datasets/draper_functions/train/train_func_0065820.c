_evas_gl_shader_file_check(const char *bin_shader_dir, char *bin_shader_file, int dir_num)
{
   char before_name[PATH_MAX];
   char after_name[PATH_MAX];
   int new_path_len = 0;
   int i = 0, j = 0;

   char *vendor = NULL;
   char *driver = NULL;
   char *version = NULL;

   vendor = (char *)glGetString(GL_VENDOR);
   driver = (char *)glGetString(GL_RENDERER);
   version = (char *)glGetString(GL_VERSION);

   new_path_len = snprintf(before_name, sizeof(before_name), "%s::%s::%s::%s::binary_shader.eet", vendor, version, driver, MODULE_ARCH);


   for (i = 0; i < new_path_len; i++)
     {
        if (before_name[i] != '/')
          {
             after_name[j] = before_name[i];
             j++;
          }
     }
   after_name[j] = 0;

   snprintf(bin_shader_file, dir_num, "%s/%s", bin_shader_dir, after_name);

   return _evas_gl_shader_file_exists(bin_shader_file);
}
