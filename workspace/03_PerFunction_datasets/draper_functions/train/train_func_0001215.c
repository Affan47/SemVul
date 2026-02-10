gap_match_number(gint32 layer_idx, const char *pattern)
{
   char        l_digit_buff[128];
   const char *l_ptr;
   int         l_idx;
   gint32      l_num, l_range_start;
   gboolean    utf8_compliant;

   utf8_compliant = g_utf8_validate(pattern, -1, NULL);
   l_idx = 0;
   l_num = -1; l_range_start = -1;
   l_ptr = pattern;
   while(1 == 1)
   {
      if(g_ascii_isdigit(*l_ptr))
      {
         l_digit_buff[l_idx] = *l_ptr;
         l_idx++;
      }
      else
      {
         if(l_idx > 0)
         {

            l_digit_buff[l_idx] = '\0';
            l_num = atol(l_digit_buff);

            if(l_num == layer_idx)
            {
               return(TRUE);
            }

            if((l_range_start >= 0)
            && (layer_idx >= l_range_start) && (layer_idx <= l_num ))
            {
               return(TRUE);
            }

            l_range_start = -1;
            l_idx = 0;
          }

          switch(*l_ptr)
          {
            case '\0':
               return (FALSE);
               break;
            case ' ':
            case '\t':
               break;
            case ',':
               l_num = -1;
               break;
            case '-':
                 if (l_num >= 0)
                 {
                    l_range_start = l_num;
                 }
                 break;
            default:


               l_num = -1;
               l_range_start = -1;

               break;
          }
      }

      if(utf8_compliant)
      {
        l_ptr = g_utf8_find_next_char(l_ptr, NULL);
      }
      else
      {
        l_ptr++;
      }
   }

   return(FALSE);
}
