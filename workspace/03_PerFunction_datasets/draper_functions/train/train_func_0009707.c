luaT_init (void)
{
  int t;
  L->IMtable_size = NUM_TAGS*2;
  L->last_tag = -(NUM_TAGS-1);
  L->IMtable = luaM_newvector(L->IMtable_size, struct IM);
  for (t=L->last_tag; t<=0; t++)
    init_entry(t);
}
