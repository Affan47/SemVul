maybe_set_return_flags (parser *p)
{
    NODE *t = p->tree;

    if (t != NULL && t->t == UFUN) {
	p->flags |= P_UFRET;
    }
}
