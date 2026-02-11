display_hash_table (object dpy)
{
  pushSTACK(dpy);
  if (!ensure_living_display(&(STACK_0)))
    error_closed_display(TheSubr(subr_self)->name,STACK_0);
  return TheStructure (popSTACK())->recdata[slot_DISPLAY_HASH_TABLE];
}
