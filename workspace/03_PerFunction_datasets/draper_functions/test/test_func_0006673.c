calc_closure_expand (struct calc_closure *cp)
{
  if (cp->win->line_count == cp->line_starts_slots)
    {
      if (cp->line_starts_slots == 0)
	cp->line_starts_slots = 100;
      cp->win->line_starts = x2nrealloc (cp->win->line_starts,
					 &cp->line_starts_slots,
					 sizeof (cp->win->line_starts[0]));
      cp->win->log_line_no = xrealloc (cp->win->log_line_no,
				     cp->line_starts_slots *
				     sizeof (cp->win->log_line_no[0]));
    }
}
