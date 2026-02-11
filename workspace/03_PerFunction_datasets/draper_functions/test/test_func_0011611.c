gap_lib_load_image (char *lod_name)
{
  char  *l_ext;
  char  *l_tmpname;
  gint32 l_tmp_image_id;
  int    l_rc;

  l_rc = 0;
  l_tmpname = NULL;
  l_ext = gap_lib_alloc_extension(lod_name);
  if(l_ext != NULL)
  {
    if((0 == strcmp(l_ext, ".xcfgz"))
    || (0 == strcmp(l_ext, ".gz")))
    {


      l_tmpname = p_gzip(lod_name, gimp_temp_name(&l_ext[1]), "unzip");
    }
    else l_tmpname = lod_name;
    g_free(l_ext);
  }

  if(l_tmpname == NULL)
  {
    return -1;
  }


  if(gap_debug) printf("DEBUG: before   gap_lib_load_image: '%s'\n", l_tmpname);

  l_tmp_image_id = gimp_file_load(GIMP_RUN_NONINTERACTIVE,
                l_tmpname,
                l_tmpname
                );

  if(gap_debug) printf("DEBUG: after    gap_lib_load_image: '%s' id=%d\n\n",
                               l_tmpname, (int)l_tmp_image_id);

  if(l_tmpname != lod_name)
  {
    g_remove(l_tmpname);
    g_free(l_tmpname);
  }


  return l_tmp_image_id;

}
