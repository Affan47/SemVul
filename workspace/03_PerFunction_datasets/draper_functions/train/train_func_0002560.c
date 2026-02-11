Perl_debop(pTHX_ const OP *o)
{
    dVAR;

    PERL_ARGS_ASSERT_DEBOP;

    if (CopSTASH_eq(PL_curcop, PL_debstash) && !DEBUG_J_TEST_)
	return 0;

    Perl_deb(aTHX_ "%s", OP_NAME(o));
    switch (o->op_type) {
    case OP_CONST:
    case OP_HINTSEVAL:


#ifdef USE_ITHREADS
	if ((((SVOP*)o)->op_sv) || !IN_PERL_COMPILETIME)
#endif
	    PerlIO_printf(Perl_debug_log, "(%s)", SvPEEK(cSVOPo_sv));
	break;
    case OP_GVSV:
    case OP_GV:
	if (cGVOPo_gv) {
	    SV * const sv = newSV(0);
#ifdef PERL_MAD


	    SvUTF8_on(sv);
#endif
	    gv_fullname3(sv, cGVOPo_gv, NULL);
	    PerlIO_printf(Perl_debug_log, "(%s)", SvPV_nolen_const(sv));
	    SvREFCNT_dec_NN(sv);
	}
	else
	    PerlIO_printf(Perl_debug_log, "(NULL)");
	break;

    {
        int count;

    case OP_PADSV:
    case OP_PADAV:
    case OP_PADHV:
        count = 1;
        goto dump_padop;
    case OP_PADRANGE:
        count = o->op_private & OPpPADRANGE_COUNTMASK;
    dump_padop:

        {
            CV * const cv = deb_curcv(cxstack_ix);
            SV *sv;
            PAD * comppad = NULL;
            int i;

            if (cv) {
                PADLIST * const padlist = CvPADLIST(cv);
                comppad = *PadlistARRAY(padlist);
            }
            PerlIO_printf(Perl_debug_log, "(");
            for (i = 0; i < count; i++) {
                if (comppad &&
                        (sv = *av_fetch(comppad, o->op_targ + i, FALSE)))
                    PerlIO_printf(Perl_debug_log, "%s", SvPV_nolen_const(sv));
                else
                    PerlIO_printf(Perl_debug_log, "[%"UVuf"]",
                            (UV)o->op_targ+i);
                if (i < count-1)
                    PerlIO_printf(Perl_debug_log, ",");
            }
            PerlIO_printf(Perl_debug_log, ")");
        }
        break;
    }

    default:
	break;
    }
    PerlIO_printf(Perl_debug_log, "\n");
    return 0;
}
