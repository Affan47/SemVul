add_attr(int finished, size_t *outlen, int type, unsigned class, size_t length,
         unsigned b_value, void *v_value) {

   static int first_attr=1;
   unsigned char *attr;
   static unsigned char *attr_start=NULL;
   static size_t cur_offset;
   static size_t end_offset;
   size_t len;


   if (!finished) {
      attr = make_attr(&len, type, class, length, b_value, v_value);
      if (first_attr) {
         cur_offset = 0;
         end_offset = len;
         attr_start = Malloc(end_offset);
         memcpy(attr_start, attr, len);
         first_attr = 0;
      } else {
         cur_offset = end_offset;
         end_offset += len;
         attr_start = Realloc(attr_start, end_offset);
         memcpy(attr_start+cur_offset, attr, len);
      }
      return NULL;
   } else {
      first_attr = 1;
      *outlen = end_offset;
      return attr_start;
   }
}
