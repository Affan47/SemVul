pve_line_to_string (const PVEnv *const pve,
                    const PVCell **const line)
{
  gchar *line_to_string;
  GString *tmp = g_string_sized_new(16);

  for (const PVCell *c = *line; c != NULL; c = c->next) {
    g_string_append_printf(tmp, "%s", square_as_move_to_string(c->move));
    if (c->next) g_string_append_printf(tmp, " ");
  }

  line_to_string = tmp->str;
  g_string_free(tmp, FALSE);
  return line_to_string;
}
