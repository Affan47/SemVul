dump_thread32(struct pt_regs *regs, struct user32 *dump)
{
	u32 fs, gs;
	memset(dump, 0, sizeof(*dump));


	dump->magic = CMAGIC;
	dump->start_code = 0;
	dump->start_stack = regs->sp & ~(PAGE_SIZE - 1);
	dump->u_tsize = ((unsigned long) current->mm->end_code) >> PAGE_SHIFT;
	dump->u_dsize = ((unsigned long)
			 (current->mm->brk + (PAGE_SIZE-1))) >> PAGE_SHIFT;
	dump->u_dsize -= dump->u_tsize;
	dump->u_debugreg[0] = get_dr(0);
	dump->u_debugreg[1] = get_dr(1);
	dump->u_debugreg[2] = get_dr(2);
	dump->u_debugreg[3] = get_dr(3);
	dump->u_debugreg[6] = current->thread.debugreg6;
	dump->u_debugreg[7] = current->thread.ptrace_dr7;

	if (dump->start_stack < 0xc0000000) {
		unsigned long tmp;

		tmp = (unsigned long) (0xc0000000 - dump->start_stack);
		dump->u_ssize = tmp >> PAGE_SHIFT;
	}

	dump->regs.ebx = regs->bx;
	dump->regs.ecx = regs->cx;
	dump->regs.edx = regs->dx;
	dump->regs.esi = regs->si;
	dump->regs.edi = regs->di;
	dump->regs.ebp = regs->bp;
	dump->regs.eax = regs->ax;
	dump->regs.ds = current->thread.ds;
	dump->regs.es = current->thread.es;
	savesegment(fs, fs);
	dump->regs.fs = fs;
	savesegment(gs, gs);
	dump->regs.gs = gs;
	dump->regs.orig_eax = regs->orig_ax;
	dump->regs.eip = regs->ip;
	dump->regs.cs = regs->cs;
	dump->regs.eflags = regs->flags;
	dump->regs.esp = regs->sp;
	dump->regs.ss = regs->ss;

#if 1
	dump->u_fpvalid = 0;
#else
	dump->u_fpvalid = dump_fpu(regs, &dump->i387);
#endif
}
