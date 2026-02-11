die_kmmio_nesting_error(struct pt_regs *regs, unsigned long addr)
{
	const struct trap_reason *my_reason = &get_cpu_var(pf_reason);
	pr_emerg("unexpected fault for address: 0x%08lx, last fault for address: 0x%08lx\n",
		 addr, my_reason->addr);
	print_pte(addr);
	print_symbol(KERN_EMERG "faulting IP is at %s\n", regs->ip);
	print_symbol(KERN_EMERG "last faulting IP was at %s\n", my_reason->ip);
#ifdef __i386__
	pr_emerg("eax: %08lx   ebx: %08lx   ecx: %08lx   edx: %08lx\n",
		 regs->ax, regs->bx, regs->cx, regs->dx);
	pr_emerg("esi: %08lx   edi: %08lx   ebp: %08lx   esp: %08lx\n",
		 regs->si, regs->di, regs->bp, regs->sp);
#else
	pr_emerg("rax: %016lx   rcx: %016lx   rdx: %016lx\n",
		 regs->ax, regs->cx, regs->dx);
	pr_emerg("rsi: %016lx   rdi: %016lx   rbp: %016lx   rsp: %016lx\n",
		 regs->si, regs->di, regs->bp, regs->sp);
#endif
	put_cpu_var(pf_reason);
	BUG();
}
