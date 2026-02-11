thread_quasi_id(void)
{
	int sp;

	if G_UNLIKELY(!thread_inited)
		thread_init();

	return thread_quasi_id_fast(&sp);
}
