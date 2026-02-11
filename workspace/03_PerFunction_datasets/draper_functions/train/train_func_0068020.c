_e_kbd_int_buf_send(E_Kbd_Int *ki)
{
   const char *str = NULL;
   const Eina_List *matches;

   matches = e_kbd_buf_string_matches_get(ki->kbuf);
   if (matches) str = matches->data;
   else str = e_kbd_buf_actual_string_get(ki->kbuf);
   if (str) _e_kbd_int_string_send(ki, str);
}
