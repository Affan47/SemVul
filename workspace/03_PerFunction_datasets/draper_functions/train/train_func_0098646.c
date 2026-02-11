CPROCESS_create(int mode, void *cmd, char *name, CARRAY *env)
{
	CPROCESS *process;


	process = OBJECT_new(CLASS_Process, name, OP  ? (OBJECT *)OP : (OBJECT *)CP);

	init_process(process);
	run_process(process, mode, cmd, env);

	OBJECT_UNREF_KEEP(process, "CPROCESS_create");

	if (!name || !*name)
		STREAM_blocking(CSTREAM_stream(process), TRUE);


	return process;
}
