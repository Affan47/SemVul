declare_start(void)
{
    register int c;
    register bucket *bp;
    static int entry_counter = 0;

    for (;;) {
      c = nextc();
      if (!isalpha(c) && c != '_' && c != '.' && c != '$') return;
      bp = get_name();

      if (bp->class == TERM)
        terminal_start(bp->name);
      bp->entry = ++entry_counter;
      if (entry_counter == 256)
        too_many_entries();
    }
}
