city_report_dialog_popup(bool raise)
{
  if(!city_dialog_shell) {
    city_dialog_shell_is_modal = FALSE;

    create_city_report_dialog(FALSE);

    select_menu_cached = FALSE;
  }

  gui_dialog_present(city_dialog_shell);
  hilite_cities_from_canvas();
  if (raise) {
    gui_dialog_raise(city_dialog_shell);
  }
}
