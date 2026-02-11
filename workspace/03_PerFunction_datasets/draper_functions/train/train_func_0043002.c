ecpg_add_mem(void *ptr, int lineno)
{
	struct auto_mem *am = (struct auto_mem *) ecpg_alloc(sizeof(struct auto_mem), lineno);

	if (!am)
		return false;

	am->pointer = ptr;
	am->next = get_auto_allocs();
	set_auto_allocs(am);
	return true;
}
