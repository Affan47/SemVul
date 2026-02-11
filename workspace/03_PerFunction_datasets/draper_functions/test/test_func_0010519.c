eio_file_chmod(const char *path,
	       mode_t mode,
	       Eio_Done_Cb done_cb,
	       Eio_Error_Cb error_cb,
	       const void *data)
{
   Eio_File_Mkdir *r = NULL;

   EINA_SAFETY_ON_NULL_RETURN_VAL(path, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(done_cb, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(error_cb, NULL);

   r = malloc(sizeof (Eio_File_Mkdir));
   if (!r) return NULL;

   r->path = eina_stringshare_add(path);
   r->mode = mode;

   if (!eio_file_set(&r->common,
		     done_cb,
		     error_cb,
		      data,
		     _eio_file_chmod,
		     _eio_file_mkdir_done,
		     _eio_file_mkdir_error))
     return NULL;

   return &r->common;
}
