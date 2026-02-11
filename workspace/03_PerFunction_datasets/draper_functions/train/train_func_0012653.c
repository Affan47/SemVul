_e_kbd_buf_actual_string_update(E_Kbd_Buf *kb)
{
   Eina_List *l;
   char *actual = NULL;
   int actual_len = 0;
   unsigned int actual_size = 0;
   E_Kbd_Buf_Keystroke *ks;

   _e_kbd_buf_actual_string_clear(kb);
   EINA_LIST_FOREACH(kb->keystrokes, l, ks)
     {
        const char *str;

        str = _e_kbd_buf_keystroke_string_get(kb, ks);
        if (!str) continue;
        if (!actual) actual_size += 64, actual = malloc(actual_size);
        else if ((actual_len + strlen(str) + 1) > actual_size)
          {
             actual_size += 64;
             actual = realloc(actual, actual_size);
          }
        strcpy(actual + actual_len, str);
        actual_len += strlen(str);
     }
   kb->actual_string = eina_stringshare_add(actual);
   free(actual);
}
