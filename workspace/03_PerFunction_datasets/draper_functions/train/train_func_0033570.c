editinfobox_spin_button_value_changed(GtkSpinButton *spinbutton,
                                                  gpointer userdata)
{
  struct editinfobox *ei;
  int which, value;
  enum editor_tool_type ett;

  ei = editgui_get_editinfobox();

  if (!ei) {
    return;
  }

  value = gtk_spin_button_get_value_as_int(spinbutton);
  which = GPOINTER_TO_INT(userdata);
  ett = editor_get_tool();

  switch (which) {
  case SPIN_BUTTON_SIZE:
    editor_tool_set_size(ett, value);
    break;
  case SPIN_BUTTON_COUNT:
    editor_tool_set_count(ett, value);
    break;
  default:
    return;
    break;
  }

  editinfobox_refresh(ei);
}
