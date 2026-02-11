Monitor_CFRD(int argc, char **argv)
{
	struct _sim_register *reg;
	char CFRegister[8];
	unsigned long Value;

	if(argc != 2) return Monitor_show_help("cfrd");
	sscanf(argv[1], "%s", CFRegister);

	reg = sim->register_lookup_by_name(CFRegister);
	if(!reg) {
		printf ("CFRegister: %s not found\n",CFRegister);
		return 1;
	}
	Memory_Retr(&Value, reg->width, memory_core.mbar + reg->offset);
	printf("CFRegister(%s) = %8lx\n", CFRegister, Value);
	return 1;
}
