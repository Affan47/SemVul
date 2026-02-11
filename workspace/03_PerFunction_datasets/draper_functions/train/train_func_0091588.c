caml_page_table_resize(void)
{
  struct page_table old = caml_page_table;
  uintnat * new_entries;
  uintnat i, h;

  caml_gc_message (0x08, "Growing page table to %lu entries\n",
                   caml_page_table.size);

  new_entries = calloc(2 * old.size, sizeof(uintnat));
  if (new_entries == NULL) {
    caml_gc_message (0x08, "No room for growing page table\n", 0);
    return -1;
  }

  caml_page_table.size = 2 * old.size;
  caml_page_table.shift = old.shift - 1;
  caml_page_table.mask = caml_page_table.size - 1;
  caml_page_table.occupancy = old.occupancy;
  caml_page_table.entries = new_entries;

  for (i = 0; i < old.size; i++) {
    uintnat e = old.entries[i];
    if (e == 0) continue;
    h = Hash(Page(e));
    while (caml_page_table.entries[h] != 0)
      h = (h + 1) & caml_page_table.mask;
    caml_page_table.entries[h] = e;
  }

  free(old.entries);
  return 0;
}
