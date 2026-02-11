get_sigframe(struct ksignal *ksig, struct pt_regs *regs,
				 size_t frame_size,
				 void __user **fpstate)
{
	struct fpu *fpu = &current->thread.fpu;
	unsigned long sp;


	sp = regs->sp;


	if (ksig->ka.sa.sa_flags & SA_ONSTACK)
		sp = sigsp(sp, ksig);

	else if ((regs->ss & 0xffff) != __USER32_DS &&
		!(ksig->ka.sa.sa_flags & SA_RESTORER) &&
		 ksig->ka.sa.sa_restorer)
		sp = (unsigned long) ksig->ka.sa.sa_restorer;

	if (fpu->fpstate_active) {
		unsigned long fx_aligned, math_size;

		sp = fpu__alloc_mathframe(sp, 1, &fx_aligned, &math_size);
		*fpstate = (struct _fpstate_32 __user *) sp;
		if (copy_fpstate_to_sigframe(*fpstate, (void __user *)fx_aligned,
				    math_size) < 0)
			return (void __user *) -1L;
	}

	sp -= frame_size;


	sp = ((sp + 4) & -16ul) - 4;
	return (void __user *) sp;
}
