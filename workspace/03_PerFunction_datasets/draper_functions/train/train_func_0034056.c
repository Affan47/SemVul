key_group_action_move_right (KeyGroup            *self,
                             const gchar         *action_name,
                             guint                key_val,
                             ClutterModifierType  modifiers)
{
  gint n_children;

  g_assert_cmpstr (action_name, ==, "move-right");
  g_assert_cmpint (key_val, ==, CLUTTER_KEY_Right);

  n_children = clutter_group_get_n_children (CLUTTER_GROUP (self));

  self->selected_index += 1;

  if (self->selected_index >= n_children)
    self->selected_index = 0;

  return TRUE;
}
