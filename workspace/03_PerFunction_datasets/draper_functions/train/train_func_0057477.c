HTS_match_head_string(const char *str, const char *pattern, size_t * matched_size)
{

   (*matched_size) = 0;
   while (1) {
      if (pattern[(*matched_size)] == '\0')
         return TRUE;
      if (str[(*matched_size)] == '\0')
         return FALSE;
      if (str[(*matched_size)] != pattern[(*matched_size)])
         return FALSE;
      (*matched_size)++;
   }
}
