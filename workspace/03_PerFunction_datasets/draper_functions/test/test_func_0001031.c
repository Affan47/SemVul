eina_xattr_fd_ls(int fd)
{
#ifdef HAVE_XATTR
   Eina_Xattr_Iterator *it;
   ssize_t length;

   if (fd < 0) return NULL;

   length = flistxattr(fd, NULL, 0);
   if (length <= 0) return NULL;

   it = calloc(1, sizeof (Eina_Xattr_Iterator) + length - 1);
   if (!it) return NULL;

   EINA_MAGIC_SET(&it->iterator, EINA_MAGIC_ITERATOR);

   it->length = flistxattr(fd, it->xattr, length);
   if (it->length != length)
     {
        free(it);
	return NULL;
     }

   it->iterator.version = EINA_ITERATOR_VERSION;
   it->iterator.next = FUNC_ITERATOR_NEXT(_eina_xattr_ls_iterator_next);
   it->iterator.get_container = FUNC_ITERATOR_GET_CONTAINER(_eina_xattr_ls_iterator_container);
   it->iterator.free = FUNC_ITERATOR_FREE(_eina_xattr_ls_iterator_free);

   return &it->iterator;
#else
   return NULL;
   (void)fd;
#endif
}
