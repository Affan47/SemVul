populate_table(struct memport_data *memport, int iswrite, offs_t start, offs_t stop, UINT8 handler)
{
	struct table_data *tabledata = iswrite ? &memport->write : &memport->read;
	int minbits = DATABITS_TO_SHIFT(memport->dbits);
	int l1bits = LEVEL1_BITS(memport->ebits);
	int l2bits = LEVEL2_BITS(memport->ebits);
	offs_t l2mask = LEVEL2_MASK(memport->ebits);
	offs_t l1start = start >> (l2bits + minbits);
	offs_t l2start = (start >> minbits) & l2mask;
	offs_t l1stop = stop >> (l2bits + minbits);
	offs_t l2stop = (stop >> minbits) & l2mask;
	UINT8 subindex;


	if (start > stop)
		return;


	if (handler != STATIC_RAM && handler != STATIC_ROM && handler != STATIC_RAMROM)
	{
		tabledata->handlers[handler].offset = start;
		tabledata->handlers[handler].top = stop;
	}


	if (handler >= STATIC_BANK1 && handler <= STATIC_BANKMAX)
	{
		if (iswrite)
			bankdata[handler].writeoffset = start;
		else
			bankdata[handler].readoffset = start;
	}


	if (l2start != 0)
	{

		subindex = tabledata->table[l1start];
		if (subindex < SUBTABLE_BASE)
			subindex = tabledata->table[l1start] = alloc_new_subtable(memport, tabledata, subindex);
		subindex &= SUBTABLE_MASK;


		if (l1start == l1stop)
		{
			memset(&tabledata->table[(1 << l1bits) + (subindex << l2bits) + l2start], handler, l2stop - l2start + 1);
			return;
		}


		memset(&tabledata->table[(1 << l1bits) + (subindex << l2bits) + l2start], handler, (1 << l2bits) - l2start);
		if (l1start != (offs_t)~0) l1start++;
	}


	if (l2stop != l2mask)
	{

		subindex = tabledata->table[l1stop];
		if (subindex < SUBTABLE_BASE)
			subindex = tabledata->table[l1stop] = alloc_new_subtable(memport, tabledata, subindex);
		subindex &= SUBTABLE_MASK;


		memset(&tabledata->table[(1 << l1bits) + (subindex << l2bits)], handler, l2stop + 1);


		if (l1start == l1stop)
			return;
		if (l1stop != 0) l1stop--;
	}


	if (l1start <= l1stop)
		memset(&tabledata->table[l1start], handler, l1stop - l1start + 1);
}
