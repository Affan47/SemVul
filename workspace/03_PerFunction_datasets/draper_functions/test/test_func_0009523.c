__gnat_is_symbolic_link_attr (char* name ATTRIBUTE_UNUSED,
                              struct file_attributes* attr)
{
   if (attr->symbolic_link == ATTR_UNSET) {
#if defined (__vxworks) || defined (__nucleus__)
      attr->symbolic_link = 0;

#elif defined (_AIX) || defined (__APPLE__) || defined (__unix__)
      int ret;
      GNAT_STRUCT_STAT statbuf;
      ret = GNAT_LSTAT (name, &statbuf);
      attr->symbolic_link = (!ret && S_ISLNK (statbuf.st_mode));
#else
      attr->symbolic_link = 0;
#endif
   }
   return attr->symbolic_link;
}
