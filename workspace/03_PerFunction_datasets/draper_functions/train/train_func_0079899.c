luaT_init (void) {
  int t;
  L->last_tag = -(NUM_TAGS-1);
  luaM_growvector(L->IMtable, 0, NUM_TAGS, struct IM, arrEM, MAX_INT);
  for (t=L->last_tag; t<=0; t++)
    init_entry(t);
}
