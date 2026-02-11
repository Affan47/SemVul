S_reg_node(pTHX_ RExC_state_t *pRExC_state, U8 op)
{
    dVAR;
    regnode *ptr;
    regnode * const ret = RExC_emit;
    GET_RE_DEBUG_FLAGS_DECL;

    PERL_ARGS_ASSERT_REG_NODE;

    if (SIZE_ONLY) {
	SIZE_ALIGN(RExC_size);
	RExC_size += 1;
	return(ret);
    }
    if (RExC_emit >= RExC_emit_bound)
        Perl_croak(aTHX_ "panic: reg_node overrun trying to emit %d, %p>=%p",
		   op, RExC_emit, RExC_emit_bound);

    NODE_ALIGN_FILL(ret);
    ptr = ret;
    FILL_ADVANCE_NODE(ptr, op);
#ifdef RE_TRACK_PATTERN_OFFSETS
    if (RExC_offsets) {
	MJD_OFFSET_DEBUG(("%s:%d: (op %s) %s %"UVuf" (len %"UVuf") (max %"UVuf").\n",
              "reg_node", __LINE__,
              PL_reg_name[op],
              (UV)(RExC_emit - RExC_emit_start) > RExC_offsets[0]
		? "Overwriting end of array!\n" : "OK",
              (UV)(RExC_emit - RExC_emit_start),
              (UV)(RExC_parse - RExC_start),
              (UV)RExC_offsets[0]));
	Set_Node_Offset(RExC_emit, RExC_parse + (op == END));
    }
#endif
    RExC_emit = ptr;
    return(ret);
}
