Perl_magic_getsig(pTHX_ SV *sv, MAGIC *mg)
{
    dVAR;

    int i = (I16)mg->mg_private;

    PERL_ARGS_ASSERT_MAGIC_GETSIG;

    if (!i) {
        STRLEN siglen;
        const char * sig = MgPV_const(mg, siglen);
        mg->mg_private = i = whichsig_pvn(sig, siglen);
    }

    if (i > 0) {
    	if(PL_psig_ptr[i])
    	    sv_setsv(sv,PL_psig_ptr[i]);
    	else {
	    Sighandler_t sigstate = rsignal_state(i);
#ifdef FAKE_PERSISTENT_SIGNAL_HANDLERS
	    if (PL_sig_handlers_initted && PL_sig_ignoring[i])
		sigstate = SIG_IGN;
#endif
#ifdef FAKE_DEFAULT_SIGNAL_HANDLERS
	    if (PL_sig_handlers_initted && PL_sig_defaulting[i])
		sigstate = SIG_DFL;
#endif

    	    if(sigstate == (Sighandler_t) SIG_IGN)
    	    	sv_setpvs(sv,"IGNORE");
    	    else
    	    	sv_setsv(sv,&PL_sv_undef);
	    PL_psig_ptr[i] = SvREFCNT_inc_simple_NN(sv);
    	    SvTEMP_off(sv);
    	}
    }
    return 0;
}
