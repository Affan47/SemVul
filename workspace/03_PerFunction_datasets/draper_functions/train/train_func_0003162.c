cp_print(const ConstantPool* constant_pool)
{
	uint16_t count;

	for(count = 1; count < constant_pool->count; count++)
		cp_entry_print(&constant_pool->entries[count], count);
}
