e_fm2_custom_file_flush(void)
{
   if (!_e_fm2_custom_file) return;

   if (_e_fm2_flush_defer)
     e_powersave_deferred_action_del(_e_fm2_flush_defer);
   _e_fm2_flush_defer =
     e_powersave_deferred_action_add(_e_fm2_custom_file_cb_defer_save, NULL);
}
