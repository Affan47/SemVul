mmio_trace_reset(struct trace_array *tr)
{
	pr_debug("in %s\n", __func__);

	disable_mmiotrace();
	mmio_reset_data(tr);
	mmio_trace_array = NULL;
}
