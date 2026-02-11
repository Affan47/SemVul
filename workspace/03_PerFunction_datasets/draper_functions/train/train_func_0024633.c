STACK_init(void)
{
	int stack;
	struct rlimit limit;
	uintptr_t max;


	if (getrlimit(RLIMIT_STACK, &limit))
		ERROR_panic("Cannot get stack size limit");

	if (limit.rlim_cur == RLIM_INFINITY)
		max = 64 << 20;
	else
		max = (uintptr_t)limit.rlim_cur;

	STACK_size = max;
	STACK_base = mmap(NULL, STACK_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);


	max -= sizeof(VALUE) * 256;

	STACK_process_stack_limit = (uintptr_t)&stack - max;

  STACK_limit = (STACK_base + STACK_size);
  STACK_frame = (STACK_CONTEXT *)STACK_limit;
  STACK_frame_count = 0;

  SP = (VALUE *)STACK_base;
}
