syn_process_serial_data (Gpm_Event *state,
			      unsigned char *data)
{

  state->buttons = 0;
  state->dx      = 0;
  state->dy      = 0;

  syn_serial_translate_data (data, &cur_report);
  if (wmode_enabled){
    syn_process_wmode_report(&cur_report);
  }
  if (tp_find_fingers(&cur_report,state)) return;
  if (wmode_enabled){
    tp_find_gestures(&cur_report);
  }

  tp_process_report (state, &cur_report);
}
