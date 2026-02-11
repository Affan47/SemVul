_eio_eina_file_copy_xattr(Ecore_Thread *thread __UNUSED__,
			  Eio_File_Progress *op __UNUSED__,
			  Eina_File *f, int out)
{
   Eina_Iterator *it;
   Eina_Xattr *attr;

   it = eina_file_xattr_value_get(f);
   EINA_ITERATOR_FOREACH(it, attr)
     {
#ifdef HAVE_XATTR
        fsetxattr(out, attr->name, attr->value, attr->length, 0);
#endif
     }
   eina_iterator_free(it);
}
