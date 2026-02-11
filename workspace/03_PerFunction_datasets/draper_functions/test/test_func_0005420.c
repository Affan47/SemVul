ex_operators(eap)
    exarg_T	*eap;
{
    oparg_T	oa;

    clear_oparg(&oa);
    oa.regname = eap->regname;
    oa.start.lnum = eap->line1;
    oa.end.lnum = eap->line2;
    oa.line_count = eap->line2 - eap->line1 + 1;
    oa.motion_type = MLINE;
#ifdef FEAT_VIRTUALEDIT
    virtual_op = FALSE;
#endif
    if (eap->cmdidx != CMD_yank)
    {
	setpcmark();
	curwin->w_cursor.lnum = eap->line1;
	beginline(BL_SOL | BL_FIX);
    }

    switch (eap->cmdidx)
    {
	case CMD_delete:
	    oa.op_type = OP_DELETE;
	    op_delete(&oa);
	    break;

	case CMD_yank:
	    oa.op_type = OP_YANK;
	    (void)op_yank(&oa, FALSE, TRUE);
	    break;

	default:
	    if ((eap->cmdidx == CMD_rshift)
#ifdef FEAT_RIGHTLEFT
				    ^ curwin->w_p_rl
#endif
						    )
		oa.op_type = OP_RSHIFT;
	    else
		oa.op_type = OP_LSHIFT;
	    op_shift(&oa, FALSE, eap->amount);
	    break;
    }
#ifdef FEAT_VIRTUALEDIT
    virtual_op = MAYBE;
#endif
    ex_may_print(eap);
}
