e_kbd_dict_word_usage_adjust(E_Kbd_Dict *kd, const char *word, int adjust)
{

   E_Kbd_Dict_Word *kw;

   kw = _e_kbd_dict_changed_write_find(kd, word);
   if (kw)
     {
        kw->usage += adjust;
        if (kd->changed.flush_timer)
          ecore_timer_del(kd->changed.flush_timer);
        kd->changed.flush_timer = ecore_timer_add(5.0, _e_kbd_dict_cb_save_flush, kd);
     }
   else
     {
        const char *line;
        int usage = 0;

        line = _e_kbd_dict_find_full(kd, word);
        if (line)
          {
             char *wd;


             wd = _e_kbd_dict_line_parse(kd, line, &usage);
             free(wd);
          }
        usage += adjust;
        _e_kbd_dict_changed_write_add(kd, word, usage);
     }
}
