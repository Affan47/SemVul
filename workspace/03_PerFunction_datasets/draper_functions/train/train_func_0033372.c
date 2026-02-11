match_rec(char string[], const char pattern[], char * star[]) {

   int c;

   ASSERT(string!=NULL);
   ASSERT(pattern!=NULL);
   ASSERT(star!=NULL);


   while ((c=*pattern++) != '*') {
      if (false) {
      } else if (c == '\0') {
         while (*string == ' ') string++;
         return *string == '\0';
      } else if (c == ' ') {
         if (*string++ != ' ') return false;
         while (*string == ' ') string++;
      } else {
         if (*string++ != c) return false;
      }
   }


   ASSERT(c=='*');

   while (*string == ' ') string++;
   *star++ = string;

   while ((c=*string++) != '\0') {
      if (c != ' ' && match_rec(string,pattern,star)) {
         ASSERT(string>star[-1]);
         *string = '\0';
         return true;
      }
   }

   return false;
}
