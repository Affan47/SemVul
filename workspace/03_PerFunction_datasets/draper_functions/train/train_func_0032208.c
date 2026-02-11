vcc_AddCall(struct vcc *tl, struct token *t)
{
	struct proccall *pc;
	struct proc *p;

	p = vcc_findproc(tl, t);
	pc = TlAlloc(tl, sizeof *pc);
	assert(pc != NULL);
	pc->p = p;
	pc->t = t;
	VTAILQ_INSERT_TAIL(&tl->curproc->calls, pc, list);
}
