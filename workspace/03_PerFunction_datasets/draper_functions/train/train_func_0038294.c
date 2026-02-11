set_qBri_functions(PISDN_ADAPTER IoAdapter) {
	if (!IoAdapter->tasks) {
		IoAdapter->tasks = MQ_INSTANCE_COUNT;
	}
	IoAdapter->MemorySize = MQ_MEMORY_SIZE;
	set_common_qBri_functions(IoAdapter);
	diva_os_set_qBri_functions(IoAdapter);
}
