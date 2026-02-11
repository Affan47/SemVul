stpui_plist_copy(stpui_plist_t *vd, const stpui_plist_t *vs)
{
  if (vs == vd)
    return;
  stp_vars_copy(vd->v, vs->v);
  vd->scaling = vs->scaling;
  vd->orientation = vs->orientation;
  vd->auto_size_roll_feed_paper = vs->auto_size_roll_feed_paper;
  vd->unit = vs->unit;
  vd->invalid_mask = vs->invalid_mask;
  vd->command_type = vs->command_type;
  stpui_plist_set_name(vd, stpui_plist_get_name(vs));
  stpui_plist_set_queue_name(vd, stpui_plist_get_queue_name(vs));
  stpui_plist_set_extra_printer_options(vd, stpui_plist_get_extra_printer_options(vs));
  stpui_plist_set_custom_command(vd, stpui_plist_get_custom_command(vs));
  stpui_plist_set_current_standard_command(vd, stpui_plist_get_current_standard_command(vs));
  stpui_plist_set_output_filename(vd, stpui_plist_get_output_filename(vs));
  stpui_plist_set_copy_count(vd, stpui_plist_get_copy_count(vs));
}
