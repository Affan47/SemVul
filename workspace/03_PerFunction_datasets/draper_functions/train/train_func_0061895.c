l3ml3p(struct PStack *st, int pr)
{
	struct l3_process *p = st->l3.proc;
	struct l3_process *np;

	while (p) {

		np = p->next;
		st->l3.l3ml3(st, pr, p);
		p = np;
	}
}
