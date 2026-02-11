vcc_CheckUseRecurse(struct vcc *tl, const struct proc *p,
    struct method *m)
{
	struct proccall *pc;
	struct procuse *pu;

	pu = vcc_FindIllegalUse(p, m);
	if (pu != NULL) {
		VSB_printf(tl->sb,
		    "'%.*s': %s from method '%.*s'.\n",
		    PF(pu->t), pu->use, PF(p->name));
		vcc_ErrWhere(tl, pu->t);
		VSB_printf(tl->sb, "\n...in subroutine \"%.*s\"\n",
		    PF(p->name));
		vcc_ErrWhere(tl, p->name);
		return (1);
	}
	VTAILQ_FOREACH(pc, &p->calls, list) {
		if (vcc_CheckUseRecurse(tl, pc->p, m)) {
			VSB_printf(tl->sb, "\n...called from \"%.*s\"\n",
			    PF(p->name));
			vcc_ErrWhere(tl, pc->t);
			return (1);
		}
	}
	return (0);
}
