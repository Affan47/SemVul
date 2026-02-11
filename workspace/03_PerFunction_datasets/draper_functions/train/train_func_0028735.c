create_shortcuts(macro_t *macro, gint size)
{
  macros = g_malloc((size + 1) * sizeof(macro_t));
  if(macros != NULL)
    {
      memcpy(macros, macro, size * sizeof(macro_t));
      macros[size].shortcut = NULL;
      macros[size].action = NULL;
    }
  else
    perror("malloc");
}
