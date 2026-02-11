_escaped_char_get(const char *s, const char *s_end)
{

   if (s[1] == '#')
     {
        static char utf8_escape[7];
        char ustr[10];
        Eina_Unicode uchar[2] = { 0, 0 };
        char *utf8_char;
        size_t len = 0;
        int base = 10;
        s += 2;

        if (tolower((unsigned char)(*s)) == 'x')
          {
             s++;
             base = 16;
          }

        len = s_end - s;
        if (len >= sizeof(ustr) + 1)
           len = sizeof(ustr);

        memcpy(ustr, s, len);
        ustr[len] = '\0';
        uchar[0] = strtol(ustr, NULL, base);

        if (uchar[0] == 0)
          return NULL;

        utf8_char = eina_unicode_unicode_to_utf8(uchar, NULL);
        strcpy(utf8_escape, utf8_char);
        free(utf8_char);

        return utf8_escape;
     }
   else
     {
        const char *map_itr, *map_end;

        map_itr = escape_strings;
        map_end = map_itr + sizeof(escape_strings);

        while (map_itr < map_end)
          {
             if (_escaped_is_eq_and_advance(s, s_end, &map_itr, map_end))
                return map_itr;
             if (map_itr < map_end)
                _escaped_advance_after_end_of_string(&map_itr);
          }
     }

   return NULL;
}
