_e_kbd_int_string_send(E_Kbd_Int *ki, const char *str)
{
   int pos, newpos, glyph;

   pos = 0;
   e_kbd_buf_word_use(ki->kbuf, str);
   for (;;)
     {
        char buf[16];

        newpos = evas_string_char_next_get(str, pos, &glyph);
        if (glyph <= 0) return;
        strncpy(buf, str + pos, newpos - pos);
        buf[newpos - pos] = 0;
        e_kbd_send_string_press(buf, 0);
        pos = newpos;
     }
}
