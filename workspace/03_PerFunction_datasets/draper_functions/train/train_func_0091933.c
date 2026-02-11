str_intern_open(int table_size)
{
    if (table_size == 0) {
        table_size = INTERN_TABLE_SIZE_INITIAL;
    }
    intern_table = make_intern_table(table_size);
    intern_table_size = table_size;

    intern_bytes_saved = 0;
    intern_allocations_saved = 0;
}
