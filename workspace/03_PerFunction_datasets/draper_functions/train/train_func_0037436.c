eio_file_xattr_int_set(const char *path,
		       const char *attribute,
		       int xattr_int,
		       Eina_Xattr_Flags flags,
		       Eio_Done_Cb done_cb,
		       Eio_Error_Cb error_cb,
		       const void *data)
{
   Eio_File_Xattr *async;

   EINA_SAFETY_ON_NULL_RETURN_VAL(path, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(attribute, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(done_cb, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(error_cb, NULL);

   async = malloc(sizeof (Eio_File_Xattr));
   if (!async) return NULL;

   async->op = EIO_XATTR_INT;
   async->todo.xint.xattr_int = xattr_int;

   return _eio_file_xattr_setup_set(async, path, attribute, flags, done_cb, error_cb, data);
}
