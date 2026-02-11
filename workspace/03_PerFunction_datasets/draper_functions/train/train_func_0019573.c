_evas_gl_common_shader_binary_save(Evas_GL_Shared *shared)
{

   Eet_File *et = NULL;
   int tmpfd;
   int res = 0;
   char bin_dir_path[PATH_MAX];
   char bin_file_path[PATH_MAX];
   char tmp_file[PATH_MAX];
   unsigned int i;

   if (!_evas_gl_shader_dir_check(bin_dir_path, sizeof(bin_dir_path)))
     {
        res = _evas_gl_shader_file_mkpath(bin_dir_path);
        if (!res) return 0;
     }

   _evas_gl_shader_file_check(bin_dir_path, bin_file_path,
                              sizeof(bin_dir_path));


   snprintf(tmp_file, sizeof(tmp_file), "%s.XXXXXX", bin_file_path);
   tmpfd = mkstemp(tmp_file);
   if (tmpfd < 0) goto error;
   close(tmpfd);


   if (!eet_init()) goto error;

   et = eet_open(tmp_file, EET_FILE_MODE_WRITE);
   if (!et) goto error;

   for (i = 0; i < sizeof (_shaders_source) / sizeof (_shaders_source[0]); ++i)
     if (!_evas_gl_common_shader_program_binary_save(&(shared->shader[_shaders_source[i].id]),
                                                     _shaders_source[i].name,
                                                     et))
       goto error;

   if (eet_close(et) != EET_ERROR_NONE) goto error;
   if (rename(tmp_file,bin_file_path) < 0) goto error;
   eet_shutdown();
   return 1;

error:
   if (et) eet_close(et);
   if (_evas_gl_shader_file_exists(tmp_file)) unlink(tmp_file);
   eet_shutdown();
   return 0;
}
