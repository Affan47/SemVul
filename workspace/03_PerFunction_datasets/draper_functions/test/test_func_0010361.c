GC_exclude_static_roots(start, finish)
GC_PTR start;
GC_PTR finish;
{
    struct exclusion * next;
    size_t next_index, i;

    if (0 == GC_excl_table_entries) {
	next = 0;
    } else {
	next = GC_next_exclusion(start);
    }
    if (0 != next) {
      if ((word)(next -> e_start) < (word) finish) {

	ABORT("exclusion ranges overlap");
      }
      if ((word)(next -> e_start) == (word) finish) {

          next -> e_start = (ptr_t)start;
	  return;
      }
      next_index = next - GC_excl_table;
      for (i = GC_excl_table_entries; i > next_index; --i) {
	GC_excl_table[i] = GC_excl_table[i-1];
      }
    } else {
      next_index = GC_excl_table_entries;
    }
    if (GC_excl_table_entries == MAX_EXCLUSIONS) ABORT("Too many exclusions");
    GC_excl_table[next_index].e_start = (ptr_t)start;
    GC_excl_table[next_index].e_end = (ptr_t)finish;
    ++GC_excl_table_entries;
}
