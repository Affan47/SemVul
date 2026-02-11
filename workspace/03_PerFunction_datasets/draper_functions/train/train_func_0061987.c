ECPGfree_auto_mem(void)
{
	struct auto_mem *am;


	for (am = auto_allocs; am;)
	{
		struct auto_mem *act = am;

		am = am->next;
		ECPGfree(act->pointer);
		ECPGfree(act);
	}

	auto_allocs = NULL;
}
