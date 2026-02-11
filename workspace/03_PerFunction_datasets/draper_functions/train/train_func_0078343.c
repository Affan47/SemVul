set_breakpoint(CLASS *class, ushort line)
{
  DEBUG_BREAK *brk;
  int id;

  if (GB.Count(Breakpoint) >= MAX_BREAKPOINT)
  {
    WARNING("Too many breakpoints");
    return TRUE;
  }

  id = find_free_breakpoint();
  if (id == 0)
  {
    WARNING("Cannot create breakpoint");
    return TRUE;
  }

  brk = (DEBUG_BREAK *)GB.Add(&Breakpoint);

  brk->id = id;
  brk->addr = NULL;
  brk->class = class;
  brk->line = line;

  #ifdef DEBUG_ME
  fprintf(stderr, "set_breakpoint: %s.%d\n", class->name, line);
  #endif

  init_breakpoint(brk);

  return FALSE;
}
