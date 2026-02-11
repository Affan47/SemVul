mk_followpos_1(e, fpos)
Re_node e;
Pset_array fpos;
{
	Pset pos;
	int i;

	switch (Op(e)) {
	case EOS:
		break;
	case OPSTAR:
		pos = Lastpos(e);
		while (pos != NULL) {
			i = pos->posnum;
			(*fpos)[i] = pset_union(Firstpos(e), (*fpos)[i], 1);
			pos = pos->nextpos;
		}
		mk_followpos_1(Child(e), fpos);
		break;
	case OPCAT:
		pos = Lastpos(Lchild(e));
		while (pos != NULL) {
			i = pos->posnum;
			(*fpos)[i] = pset_union(Firstpos(Rchild(e)), (*fpos)[i], 1);
			pos = pos->nextpos;
		}
		mk_followpos_1(Lchild(e), fpos);
		mk_followpos_1(Rchild(e), fpos);
		break;
	case OPOPT:
		mk_followpos_1(Child(e), fpos);
		break;
	case OPALT:
		mk_followpos_1(Lchild(e), fpos);
		mk_followpos_1(Rchild(e), fpos);
		break;
	case LITERAL:
		break;
	default:
		fprintf(stderr, "mk_followpos: unknown node type %d\n", Op(e));
	}
	return;
}
