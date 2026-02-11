_ecore_imf_evas_event_locks_wrap(Evas_Lock *evas_locks,
                                 Ecore_IMF_Keyboard_Locks *imf_keyboard_locks)
{
   if (!evas_locks || !imf_keyboard_locks)
     return;

   *imf_keyboard_locks = ECORE_IMF_KEYBOARD_LOCK_NONE;
   if (evas_key_lock_is_set(evas_locks, "Num_Lock"))
     *imf_keyboard_locks |= ECORE_IMF_KEYBOARD_LOCK_NUM;
   if (evas_key_lock_is_set(evas_locks, "Caps_Lock"))
     *imf_keyboard_locks |= ECORE_IMF_KEYBOARD_LOCK_CAPS;
   if (evas_key_lock_is_set(evas_locks, "Scroll_Lock"))
     *imf_keyboard_locks |= ECORE_IMF_KEYBOARD_LOCK_SCROLL;
}
