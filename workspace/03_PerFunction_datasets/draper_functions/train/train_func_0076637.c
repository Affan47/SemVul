printprog(Prog *p)
{
	Inst *pc, *e;

	pc = p->start;
	e = p->start + p->len;

	for(; pc < e; pc++) {
		switch(pc->opcode) {
		default:
			fatal("printprog");
		case Split:
			printf("%2d. split %d, %d\n", (int)(pc-p->start), (int)(pc->x-p->start), (int)(pc->y-p->start));
			break;
		case Jmp:
			printf("%2d. jmp %d\n", (int)(pc-p->start), (int)(pc->x-p->start));
			break;
		case Char:
			printf("%2d. char %c\n", (int)(pc-p->start), pc->c);
			break;
		case Any:
			printf("%2d. any\n", (int)(pc-p->start));
			break;
		case Match:
			printf("%2d. match\n", (int)(pc-p->start));
			break;
		case Save:
			printf("%2d. save %d\n", (int)(pc-p->start), pc->n);
		}
	}
}
