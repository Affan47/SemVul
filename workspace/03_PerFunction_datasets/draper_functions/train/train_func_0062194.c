set_current_printer(void)
{
  pv = &(stpui_plist[stpui_plist_current]);
  if (print_mode_is_color(pv->v))
    stp_set_string_parameter(pv->v, "PrintingMode", "Color");
  else
    stp_set_string_parameter(pv->v, "PrintingMode", "BW");
}
