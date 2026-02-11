S_op_integerize(pTHX_ OP *o)
{
    I32 type = o->op_type;

    PERL_ARGS_ASSERT_OP_INTEGERIZE;


    if ((PL_opargs[type] & OA_OTHERINT) && (PL_hints & HINT_INTEGER))
    {
	dVAR;
	o->op_ppaddr = PL_ppaddr[++(o->op_type)];
    }

    if (type == OP_NEGATE)

	cUNOPo->op_first->op_private &= ~OPpCONST_STRICT;

    return o;
}
