Perl_pad_push(pTHX_ PADLIST *padlist, int depth)
{
    dVAR;

    PERL_ARGS_ASSERT_PAD_PUSH;

    if (depth > PadlistMAX(padlist) || !PadlistARRAY(padlist)[depth]) {
	PAD** const svp = PadlistARRAY(padlist);
	AV* const newpad = newAV();
	SV** const oldpad = AvARRAY(svp[depth-1]);
	I32 ix = AvFILLp((const AV *)svp[1]);
        const I32 names_fill = AvFILLp((const AV *)svp[0]);
	SV** const names = AvARRAY(svp[0]);
	AV *av;

	for ( ;ix > 0; ix--) {
	    if (names_fill >= ix && names[ix] != &PL_sv_undef) {
		const char sigil = SvPVX_const(names[ix])[0];
		if ((SvFLAGS(names[ix]) & SVf_FAKE)
			|| (SvFLAGS(names[ix]) & SVpad_STATE)
			|| sigil == '&')
		{

		    av_store(newpad, ix, SvREFCNT_inc(oldpad[ix]));
		}
		else {
		    SV *sv;
		    if (sigil == '@')
			sv = MUTABLE_SV(newAV());
		    else if (sigil == '%')
			sv = MUTABLE_SV(newHV());
		    else
			sv = newSV(0);
		    av_store(newpad, ix, sv);
		    SvPADMY_on(sv);
		}
	    }
	    else if (IS_PADGV(oldpad[ix]) || IS_PADCONST(oldpad[ix])) {
		av_store(newpad, ix, SvREFCNT_inc_NN(oldpad[ix]));
	    }
	    else {

		SV * const sv = newSV(0);
		av_store(newpad, ix, sv);
		SvPADTMP_on(sv);
	    }
	}
	av = newAV();
	av_store(newpad, 0, MUTABLE_SV(av));
	AvREIFY_only(av);

	padlist_store(padlist, depth, newpad);
    }
}
