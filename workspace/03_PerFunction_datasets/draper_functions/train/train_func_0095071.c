run_plant_and_detach_test(int is_early)
{
	char before[BREAK_INSTR_SIZE];
	char after[BREAK_INSTR_SIZE];

	probe_kernel_read(before, (char *)kgdbts_break_test,
	  BREAK_INSTR_SIZE);
	init_simple_test();
	ts.tst = plant_and_detach_test;
	ts.name = "plant_and_detach_test";

	if (!is_early)
		kgdb_breakpoint();
	probe_kernel_read(after, (char *)kgdbts_break_test,
	  BREAK_INSTR_SIZE);
	if (memcmp(before, after, BREAK_INSTR_SIZE)) {
		printk(KERN_CRIT "kgdbts: ERROR kgdb corrupted memory\n");
		panic("kgdb memory corruption");
	}


	if (!is_early)
		kgdbts_break_test();
}
