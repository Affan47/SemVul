_e_mod_kbd_slide(int visible, double len)
{
   _e_illume_kbd->start = ecore_loop_time_get();
   _e_illume_kbd->len = len;
   _e_illume_kbd->adjust_start = _e_illume_kbd->adjust;
   _e_illume_kbd->adjust_end = 0;
   if ((visible) && (_e_illume_kbd->border))
     _e_illume_kbd->adjust_end = _e_illume_kbd->border->h;
   if (!_e_illume_kbd->animator)
     _e_illume_kbd->animator = ecore_animator_add(_e_mod_kbd_cb_animate, NULL);
}
