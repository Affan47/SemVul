cl_com_copy_in_addr(struct in_addr *addr) {
   struct in_addr* copy = NULL;

   if (addr == NULL) {
      return NULL;
   }

   copy = (struct in_addr*) malloc(sizeof(struct in_addr));
   if (copy != NULL) {
      memcpy((char*) copy , addr, sizeof(struct in_addr));
   }
   return copy;
}
