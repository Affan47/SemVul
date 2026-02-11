grab_key (KeySym keysym, unsigned int modifiers, Window grab_window)
{
  unsigned int mod_list[8];
  int i;
  KeyCode keycode;
  unsigned int mod;


  modifiers = rp_mask_to_x11_mask (modifiers);
  if (!keysym_to_keycode_mod (keysym, &keycode, &mod))
    return;
  PRINT_DEBUG (("keycode_mod: %ld %d %d\n", keysym, keycode, mod));
  modifiers |= mod;


  mod_list[0] = 0;
  mod_list[1] = LockMask;
  mod_list[2] = rp_modifier_info.num_lock_mask;
  mod_list[3] = mod_list[1] | mod_list[2];
  mod_list[4] = rp_modifier_info.scroll_lock_mask;
  mod_list[5] = mod_list[1] | mod_list[4];
  mod_list[6] = mod_list[2] | mod_list[4];
  mod_list[7] = mod_list[1] | mod_list[2] | mod_list[4];


  for (i=0; i<8; i++)
    {
      XGrabKey(dpy, keycode, modifiers | mod_list[i],
               grab_window, True, GrabModeAsync, GrabModeAsync);
    }
}
