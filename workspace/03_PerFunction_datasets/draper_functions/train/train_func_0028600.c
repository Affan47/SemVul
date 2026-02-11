_letters_count(const char *str)
{
   int pos = 0;
   int code = 0, chnum;

   for (chnum = 0;; chnum++)
     {
        pos = evas_string_char_next_get(str, pos, &code);
        if (code == 0) break;
     }

   return chnum;
}
