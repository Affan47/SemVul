sge_read_token(const char *file)
{
   SGE_STRUCT_STAT sb;
   int fd;
   char *tokenbuf;
   size_t size;

   DENTER(TOP_LAYER, "sge_read_token");

   if (SGE_STAT(file, &sb)) {
      DTRACE;
      return NULL;
   }

   size = sb.st_size + 1;
   if (((SGE_OFF_T)size != sb.st_size + 1)
       || (tokenbuf = (char *) malloc(size)) == NULL) {
      DTRACE;
      return NULL;
   }

   if ((fd = SGE_OPEN2(file, O_RDONLY)) == -1) {
      DTRACE;
      return NULL;
   }

   if (read(fd, tokenbuf, sb.st_size) != sb.st_size) {
      DTRACE;
      close(fd);
      return NULL;
   }

   tokenbuf[sb.st_size] = '\0';

   close(fd);
   DEXIT;
   return tokenbuf;
}
