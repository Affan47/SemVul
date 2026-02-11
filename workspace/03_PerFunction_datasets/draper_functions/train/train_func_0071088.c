checkclearopq(oap)
    oparg_T	*oap;
{
    if (oap->op_type == OP_NOP
#ifdef FEAT_VISUAL
	    && !VIsual_active
#endif
	    )
	return FALSE;
    clearopbeep(oap);
    return TRUE;
}
