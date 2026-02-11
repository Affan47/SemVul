String_contains_i(const char* s, const char* match) {
   int lens = strlen(s);
   int lenmatch = strlen(match);
   for (int i = 0; i < lens-lenmatch; i++) {
      if (strncasecmp(s, match, strlen(match)) == 0)
         return 1;
      s++;
   }
   return 0;
}
