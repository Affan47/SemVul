gru_kservices_exit(void)
{
	if (gru_free_kernel_contexts())
		BUG();
}
