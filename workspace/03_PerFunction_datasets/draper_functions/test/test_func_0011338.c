feedkey_gtab_release(KeySym xkey, int kbstate)
{
  gint64 kpt;

  switch (xkey) {
     case XK_Control_L:
     case XK_Control_R:
       kpt = key_press_time_ctrl;
       key_press_time_ctrl = 0;
        if (current_time() - kpt < 300000 && tss.pre_selN) {
          if (!test_mode) {
            tss.ctrl_pre_sel = TRUE;
          }
          return 1;
        } else
          return 0;
#if 1
     case XK_Shift_L:
     case XK_Shift_R:
       kpt = key_press_time;
       key_press_time = 0;


        if (
(  (tsin_chinese_english_toggle_key == TSIN_CHINESE_ENGLISH_TOGGLE_KEY_Shift) ||
   (tsin_chinese_english_toggle_key == TSIN_CHINESE_ENGLISH_TOGGLE_KEY_ShiftL
     && xkey == XK_Shift_L) ||
   (tsin_chinese_english_toggle_key == TSIN_CHINESE_ENGLISH_TOGGLE_KEY_ShiftR
     && xkey == XK_Shift_R))
          &&  current_time() - kpt < 300000) {
          if (!test_mode) {
            tsin_toggle_eng_ch();
          }
          return 1;
        } else
          return 0;
#endif
     default:
        return 0;
  }
}
