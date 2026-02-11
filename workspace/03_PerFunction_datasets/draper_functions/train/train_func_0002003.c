sm_realloc(const char *fname, int lineno, void *ptr, unsigned int size)
{
   unsigned osize;
   void *buf;
   char *cp = (char *) ptr;

   Dmsg4(1400, "sm_realloc %s:%d %p %d\n", get_basename(fname), (uint32_t)lineno, ptr, size);
   if (size <= 0) {
      e_msg(fname, lineno, M_ABORT, 0, _("sm_realloc size: %d\n"), size);
   }


   if (ptr == NULL) {
      return sm_malloc(fname, lineno, size);
   }


   cp -= HEAD_SIZE;
   struct abufhead *head = (struct abufhead *)cp;
   osize = head->ablen - (HEAD_SIZE + 1);
   if (size == osize) {
      return ptr;
   }


   if ((buf = smalloc(fname, lineno, size)) != NULL) {
      memcpy(buf, ptr, (int)sm_min(size, osize));


      if (size > osize) {
         memset(((char *) buf) + osize, 0x55, (int) (size - osize));
      }


      sm_free(fname, lineno, ptr);
   }
   Dmsg4(4150, _("sm_realloc %d at %p from %s:%d\n"), size, buf, get_basename(fname), (uint32_t)lineno);
   return buf;
}
