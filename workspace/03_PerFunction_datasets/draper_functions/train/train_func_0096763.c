cmd_vdump (int interactive, struct cmdarg **args)
{
  char *input;
  struct cmdarg *arg;
  int which = ARG(0, number);

  rp_virtual *cur;
  rp_screen *screen = current_screen();

  arg = xmalloc (sizeof(struct cmdarg));

  PRINT_DEBUG (("virtual workspace config:\n"));

  list_for_each_entry (cur, &rp_virtuals, node) {
    PRINT_DEBUG ((" %d: %s\n", cur->number, cur->fconfig));
  }

  return cmdret_new (RET_SUCCESS, NULL);
}
