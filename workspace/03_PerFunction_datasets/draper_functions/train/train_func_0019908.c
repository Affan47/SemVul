ui_set_control_button (control_button_t item, gboolean state)
{
  GSList *btn;
  g_return_if_fail (item >= Control_PlayerButtons && item < Control_Buttons);
  no_recursion = TRUE;
  if (c_buttons[item] &&
      (GTK_TOGGLE_BUTTON(c_buttons[item]->data))->active != state)
    foreach_glist (btn, c_buttons[item])
      g_object_set (G_OBJECT(btn->data), "active", state, NULL);
  no_recursion = FALSE;
}
