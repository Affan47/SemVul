read_keymap (struct argspec *spec, struct sbuf *s, struct cmdarg **arg)
{
  char *input;
  if (s)
    input = xstrdup (sbuf_get (s));
  else
    input = get_input (spec->prompt, hist_KEYMAP, keymap_completions);

  if (input)
    {
      rp_keymap *map;
      map = find_keymap (input);
      if (map == NULL)
        {
          cmdret *ret = cmdret_new (RET_FAILURE, "unknown keymap '%s'", input);
          free (input);
          return ret;
        }
      *arg = xmalloc (sizeof(struct cmdarg));
      (*arg)->type = spec->type;
      (*arg)->arg.keymap = map;
      (*arg)->string = input;
      return NULL;
    }

  *arg = NULL;
  return cmdret_new (RET_SUCCESS, NULL);
}
