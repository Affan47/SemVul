stub_find_by_slot(int slot)
{
   const struct mapi_stub *stub =
      search_table_by_slot(public_stubs, ARRAY_SIZE(public_stubs), slot);
   if (stub)
      return stub;
   return search_table_by_slot(dynamic_stubs, num_dynamic_stubs, slot);
}
