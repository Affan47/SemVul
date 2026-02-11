check_single_step(char *put_str, char *arg)
{
	unsigned long addr = lookup_addr(arg);
	static int matched_id;


	kgdb_hex2mem(&put_str[1], (char *)kgdbts_gdb_regs,
		 NUMREGBYTES);
	gdb_regs_to_pt_regs(kgdbts_gdb_regs, &kgdbts_regs);
	v2printk("Singlestep stopped at IP: %lx\n",
		   instruction_pointer(&kgdbts_regs));

	if (sstep_thread_id != cont_thread_id) {


		v2printk("ThrID does not match: %lx\n", cont_thread_id);
		if (arch_needs_sstep_emulation) {
			if (matched_id &&
			    instruction_pointer(&kgdbts_regs) != addr)
				goto continue_test;
			matched_id++;
			ts.idx -= 2;
			sstep_state = 0;
			return 0;
		}
		cont_instead_of_sstep = 1;
		ts.idx -= 4;
		return 0;
	}
continue_test:
	matched_id = 0;
	if (instruction_pointer(&kgdbts_regs) == addr) {
		eprintk("kgdbts: SingleStep failed at %lx\n",
			   instruction_pointer(&kgdbts_regs));
		return 1;
	}

	return 0;
}
