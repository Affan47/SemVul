io_get_line(io_t * io, char string[], int size) {

   int src, dst;
   int c;

   ASSERT(io_is_ok(io));
   ASSERT(string!=NULL);
   ASSERT(size>=256);

   src = 0;
   dst = 0;

   while (true) {


      if (src >= io->in_size) {
         if (io->in_eof) {
            my_log("< %s EOF\n",io->name);
            return false;
         } else {
            my_fatal("io_get_line(): no EOL in buffer\n");
         }
      }


      if (dst >= size) my_fatal("io_get_line(): buffer overflow\n");


      c = io->in_buffer[src++];

      if (c == LF) {
         string[dst] = '\0';
         break;
      } else if (c != CR) {
         string[dst++] = c;
      }
   }


   ASSERT(src>0);

   io->in_size -= src;
   ASSERT(io->in_size>=0);

   if (io->in_size > 0) memmove(&io->in_buffer[0],&io->in_buffer[src],io->in_size);


   my_log("< %s %s\n",io->name,string);

   return true;
}
