mapi_table_fill(struct mapi_table *tbl, const mapi_proc *procs)
{
   const struct mapi_table *noop = table_get_noop();
   int i;

   for (i = 0; i < mapi_num_stubs; i++) {
      const struct mapi_stub *stub = mapi_stub_map[i];
      int slot = stub_get_slot(stub);
      mapi_func func = (mapi_func) procs[i];

      if (!func)
         func = table_get_func(noop, slot);
      table_set_func(tbl, slot, func);
   }
}
