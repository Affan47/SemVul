rarvm_init(rarvm_data_t *rarvm_data)
{
	rarvm_data->mem = (uint8_t *) rar_malloc(RARVM_MEMSIZE+4);
	if (!rarvm_data->mem) {
		return FALSE;
	}
	return TRUE;
}
