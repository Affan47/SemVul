console_display(int idx, struct user_entry *e)
{
  struct console_info *i = e->u.extra;

  if (dcc[idx].user && (dcc[idx].user->flags & USER_MASTER)) {
    dprintf(idx, "  %s\n", CONSOLE_SAVED_SETTINGS);
    dprintf(idx, "    %s %s\n", CONSOLE_CHANNEL, i->channel);
    dprintf(idx, "    %s %s, %s %s, %s %s\n", CONSOLE_FLAGS,
            masktype(i->conflags), CONSOLE_STRIPFLAGS,
            stripmasktype(i->stripflags), CONSOLE_ECHO,
            i->echoflags ? CONSOLE_YES : CONSOLE_NO);
    dprintf(idx, "    %s %d, %s %s%d\n", CONSOLE_PAGE_SETTING, i->page,
            CONSOLE_CHANNEL2, (i->conchan < GLOBAL_CHANS) ? "" : "*",
            i->conchan % GLOBAL_CHANS);
  }
}
