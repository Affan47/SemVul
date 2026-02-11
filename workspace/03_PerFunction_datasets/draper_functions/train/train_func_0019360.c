Clock_GetWord (char **Start, char **End, char word[30],
                          int *wordType)
{
   char *ptr;
   int cnt;
   int f_integer;

   *wordType = WT_NONE;
   if (*Start == NULL) {
      return -1;
   }
   ptr = *Start;

   while ((*ptr == ' ') || (*ptr == ',') || (*ptr == '.')) {
      ptr++;
   }

   if (*ptr == '\0') {
      return -1;
   }
   *Start = ptr;

   cnt = 0;
   f_integer = 1;
   while ((*ptr != ' ') && (*ptr != ',') && (*ptr != '\0')) {
      if (cnt < 29) {
         word[cnt] = (char) toupper (*ptr);
         cnt++;
      }
      if (*ptr == ':') {
         if (*wordType == WT_NONE)
            *wordType = WT_COLON;
         f_integer = 0;
      } else if (*ptr == '/') {
         if (*wordType == WT_NONE)
            *wordType = WT_SLASH;
         f_integer = 0;
      } else if (*ptr == '-') {
         if (ptr != *Start) {
            if (*wordType == WT_NONE)
               *wordType = WT_DASH;
            f_integer = 0;
         }
      } else if (*ptr == '.') {
         if (!isdigit (*(ptr + 1))) {
            break;
         } else {
            f_integer = 0;
         }
      } else if (!isdigit (*ptr)) {
         f_integer = 0;
      }
      ptr++;
   }
   word[cnt] = '\0';
   *End = ptr;
   if (f_integer) {
      *wordType = WT_INTEGER;
   }
   return 0;
}
