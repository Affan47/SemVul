_eio_file_xattr_get(void *data, Ecore_Thread *thread)
{
   Eio_File_Xattr *async = data;
   Eina_Bool failure = EINA_FALSE;
   const char *file;
   const char *attribute;

   file = async->path;
   attribute = async->attribute;

   switch (async->op)
     {
     case EIO_XATTR_DATA:
       async->todo.xdata.xattr_size = 0;
       async->todo.xdata.xattr_data = NULL;

       async->todo.xdata.xattr_data = eina_xattr_get(file, attribute, &async->todo.xdata.xattr_size);
       if (!async->todo.xdata.xattr_data) failure = EINA_TRUE;
       break;
     case EIO_XATTR_STRING:
       async->todo.xstring.xattr_string = eina_xattr_string_get(file, attribute);
       if (!async->todo.xstring.xattr_string) failure = EINA_TRUE;
       break;
     case EIO_XATTR_DOUBLE:
       failure = !eina_xattr_double_get(file, attribute, &async->todo.xdouble.xattr_double);
       break;
     case EIO_XATTR_INT:
       failure = !eina_xattr_int_get(file, attribute, &async->todo.xint.xattr_int);
       break;
     }

   if (failure)
     ecore_thread_cancel(thread);
}
