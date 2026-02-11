sge_infotext_get_next_word(dstring* buf, char* text) {
   char* p1;
   char* buffer;
   int i,b,not_last,nr_spaces;
   int start;

   sge_dstring_copy_string(buf,text);
   buffer = (char*)sge_dstring_get_string(buf);
   p1 = buffer;
   nr_spaces = 0;
   for (start=0;start<strlen(buffer);start++) {
      if ( buffer[start] == ' ' ) {
         nr_spaces++;
         continue;
      } else {
         break;
      }
   }
   if (nr_spaces > 1) {
      int stop;
      stop = strlen(p1);
      for (i=0;i<stop;i++) {
          if( p1[i] != ' ') {
             p1[i-1] = 0;
             break;
          }
      }
      return p1;
   }

   if (nr_spaces == 1) {
      p1++;
   }


   for (i=0;i<strlen(p1);i++) {
      if( p1[i] == ' ') {
         not_last = 0;
         for(b=i;b<strlen(p1);b++) {
            if (p1[b] != ' ') {
               not_last = 1;
               break;
            }
         }
         if (not_last == 1) {
            p1[i] = 0;
         }
         break;
      }
      if( p1[i] == '\n') {
         p1[i+1] = 0;
         break;
      }
   }
   return p1;
}
