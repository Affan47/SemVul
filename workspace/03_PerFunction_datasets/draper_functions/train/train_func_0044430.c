Perl_op_append_list(pTHX_ I32 type, OP *first, OP *last)
{
    if (!first)
	return last;

    if (!last)
	return first;

    if (first->op_type != (unsigned)type)
	return op_prepend_elem(type, first, last);

    if (last->op_type != (unsigned)type)
	return op_append_elem(type, first, last);

    ((LISTOP*)first)->op_last->op_sibling = ((LISTOP*)last)->op_first;
    ((LISTOP*)first)->op_last = ((LISTOP*)last)->op_last;
    first->op_flags |= (last->op_flags & OPf_KIDS);

#ifdef PERL_MAD
    if (((LISTOP*)last)->op_first && first->op_madprop) {
	MADPROP *mp = ((LISTOP*)last)->op_first->op_madprop;
	if (mp) {
	    while (mp->mad_next)
		mp = mp->mad_next;
	    mp->mad_next = first->op_madprop;
	}
	else {
	    ((LISTOP*)last)->op_first->op_madprop = first->op_madprop;
	}
    }
    first->op_madprop = last->op_madprop;
    last->op_madprop = 0;
#endif

    S_op_destroy(aTHX_ last);

    return first;
}
