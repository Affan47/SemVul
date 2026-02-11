eina_stringshare_add(const char *str)
{
   int slen;
   if (!str)
     return NULL;

   if      (str[0] == '\0')
     slen = 0;
   else if (str[1] == '\0')
     slen = 1;
   else if (str[2] == '\0')
     slen = 2;
   else if (str[3] == '\0')
     slen = 3;
   else
     slen = 3 + (int)strlen(str + 3);

   return eina_stringshare_add_length(str, slen);
}
