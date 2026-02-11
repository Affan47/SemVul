HTS_Question_load(HTS_Question * question, HTS_File * fp)
{
   char buff[HTS_MAXBUFLEN];
   HTS_Pattern *pattern, *last_pattern;

   if (question == NULL || fp == NULL)
      return FALSE;

   HTS_Question_clear(question);


   if (HTS_get_pattern_token(fp, buff) == FALSE)
      return FALSE;
   question->string = HTS_strdup(buff);


   if (HTS_get_pattern_token(fp, buff) == FALSE) {
      HTS_Question_clear(question);
      return FALSE;
   }

   last_pattern = NULL;
   if (strcmp(buff, "{") == 0) {
      while (1) {
         if (HTS_get_pattern_token(fp, buff) == FALSE) {
            HTS_Question_clear(question);
            return FALSE;
         }
         pattern = (HTS_Pattern *) HTS_calloc(1, sizeof(HTS_Pattern));
         if (question->head != NULL)
            last_pattern->next = pattern;
         else
            question->head = pattern;
         pattern->string = HTS_strdup(buff);
         pattern->next = NULL;
         if (HTS_get_pattern_token(fp, buff) == FALSE) {
            HTS_Question_clear(question);
            return FALSE;
         }
         if (!strcmp(buff, "}"))
            break;
         last_pattern = pattern;
      }
   }
   return TRUE;
}
