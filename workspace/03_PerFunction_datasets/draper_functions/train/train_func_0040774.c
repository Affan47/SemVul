init(int length)
{
    if (length) {
        if (no_of_bases.shortTable) {
            delete no_of_bases.shortTable;
            no_of_bases.shortTable = 0;
#ifdef COUNT_BASES_TABLE_SIZE
            bases_table_size -= (no_of_entries+1)*table_entry_size;
#endif
        }

        no_of_entries = length;
        int new_size = (no_of_entries+1)*table_entry_size;
        no_of_bases.shortTable = (unsigned char*)new char[new_size];
        memset(no_of_bases.shortTable, 0, new_size);
#ifdef COUNT_BASES_TABLE_SIZE
        bases_table_size += new_size;
        printf("bases_table_size = %li\n", bases_table_size);
#endif
    }
}
