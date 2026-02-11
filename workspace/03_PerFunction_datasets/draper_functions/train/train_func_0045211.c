set_header_extension (int entry, zword val)
{
    zword addr;

    if (h_extension_table == 0 || entry > hx_table_size)
	return;

    addr = h_extension_table + 2 * entry;
    SET_WORD (addr, val)

}
