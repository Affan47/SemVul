_e_kbd_dict_find_full(E_Kbd_Dict *kd, const char *word)
{
   const char *p;
   int len;

   p = _e_kbd_dict_find(kd, word);
   if (!p) return NULL;
   len = strlen(word);
   if (isspace(p[len])) return p;
   return NULL;
}
