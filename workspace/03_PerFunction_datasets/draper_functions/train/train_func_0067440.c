evas_common_language_script_type_get(const Eina_Unicode *str, size_t len)
{
   Evas_Script_Type script = EVAS_SCRIPT_COMMON;
   const Eina_Unicode *end = str + len;

   for ( ; str < end && ((script = evas_common_language_char_script_get(*str)) < EVAS_SCRIPT_ARABIC) ; str++)
     ;
   return script;
}
