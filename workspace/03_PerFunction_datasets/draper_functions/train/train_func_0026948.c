add(const ED4_bases_table& other, int start, int end)
{
    e4_assert(no_of_entries==other.no_of_entries);
    e4_assert(start>=0);
    e4_assert(end<no_of_entries);
    e4_assert(start<=end);

    int i;
    if (table_entry_size==SHORT_TABLE_ELEM_SIZE) {
        if (other.table_entry_size==SHORT_TABLE_ELEM_SIZE) {
            for (i=start; i<=end; i++) {
                set_elem_short(i, get_elem_short(i)+other.get_elem_short(i));
            }
        }
        else {
            for (i=start; i<=end; i++) {
                set_elem_short(i, get_elem_short(i)+other.get_elem_long(i));
            }
        }
    }
    else {
        if (other.table_entry_size==SHORT_TABLE_ELEM_SIZE) {
            for (i=start; i<=end; i++) {
                set_elem_long(i, get_elem_long(i)+other.get_elem_short(i));
            }
        }
        else {
            for (i=start; i<=end; i++) {
                set_elem_long(i, get_elem_long(i)+other.get_elem_long(i));
            }
        }
    }
}
