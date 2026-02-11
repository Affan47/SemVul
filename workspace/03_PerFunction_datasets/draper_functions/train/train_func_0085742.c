calculate_comment_body_indent(cmt_reflow &cmt, const char *str, int len)
{
   int idx       = 0;
   int first_len = 0;
   int last_len  = 0;
   int width     = 0;

   cmt.xtra_indent = 0;

   if (!cpd.settings[UO_cmt_indent_multi].b)
   {
      return;
   }

   if (cpd.settings[UO_cmt_multi_check_last].b)
   {

      for (idx = len - 1; idx > 0; idx--)
      {
         if ((str[idx] == '\n') || (str[idx] == '\r'))
         {
            idx++;
            while ((idx < len) && ((str[idx] == ' ') || (str[idx] == '\t')))
            {
               idx++;
            }
            last_len = len - idx;
            break;
         }
      }
   }


   for (idx = 0; idx < len; idx++)
   {
      if ((str[idx] == '\n') || (str[idx] == '\r'))
      {
         first_len = idx;
         while ((str[first_len - 1] == ' ') || (str[first_len - 1] == '\t'))
         {
            first_len--;
         }


         if ((str[idx] == '\r') && (str[idx + 1] == '\n'))
         {
            idx++;
         }
         idx++;
         break;
      }
   }


   width = 0;
   for (; idx < len - 1; idx++)
   {
      if ((str[idx] == ' ') || (str[idx] == '\t'))
      {
         if (width > 0)
         {
            break;
         }
         continue;
      }
      if ((str[idx] == '\n') || (str[idx] == '\r'))
      {

         break;
      }


      if ((str[idx] == '*') ||
          (str[idx] == '|') ||
          (str[idx] == '\\') ||
          (str[idx] == '#') ||
          (str[idx] == '+'))
      {
         width++;
      }
      else
      {
         width = 0;
         break;
      }
   }


   if ((first_len == last_len) && ((first_len > 4) || (first_len == width)))
   {
      return;
   }

   cmt.xtra_indent = ((width == 2) ? 0 : 1);
}
