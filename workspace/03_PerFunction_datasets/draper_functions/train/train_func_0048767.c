pve_line_print_internals (const PVEnv *const pve,
                          const PVCell **const line)
{
  gchar *line_to_string;
  GString *tmp = g_string_sized_new(32);

  g_string_append_printf(tmp, "line_address=%p, first_cell=%p", (void *) line, (void *) *line);
  if (*line) g_string_append_printf(tmp, ", chain: ");
  for (const PVCell *c = *line; c != NULL; c = c->next) {
    g_string_append_printf(tmp, "(c=%p, m=%s, n=%p)", (void *) c, square_as_move_to_string(c->move), (void *) c->next);
  }

  line_to_string = tmp->str;
  g_string_free(tmp, FALSE);
  return line_to_string;
}
