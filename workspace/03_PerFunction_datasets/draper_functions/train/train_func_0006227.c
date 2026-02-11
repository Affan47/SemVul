Perl_regfree_internal(pTHX_ REGEXP * const rx)
{
    dVAR;
    struct regexp *const r = ReANY(rx);
    RXi_GET_DECL(r,ri);
    GET_RE_DEBUG_FLAGS_DECL;

    PERL_ARGS_ASSERT_REGFREE_INTERNAL;

    DEBUG_COMPILE_r({
	if (!PL_colorset)
	    reginitcolors();
	{
	    SV *dsv= sv_newmortal();
            RE_PV_QUOTED_DECL(s, RX_UTF8(rx),
                dsv, RX_PRECOMP(rx), RX_PRELEN(rx), 60);
            PerlIO_printf(Perl_debug_log,"%sFreeing REx:%s %s\n",
                PL_colors[4],PL_colors[5],s);
        }
    });
#ifdef RE_TRACK_PATTERN_OFFSETS
    if (ri->u.offsets)
        Safefree(ri->u.offsets);
#endif
    if (ri->code_blocks) {
	int n;
	for (n = 0; n < ri->num_code_blocks; n++)
	    SvREFCNT_dec(ri->code_blocks[n].src_regex);
	Safefree(ri->code_blocks);
    }

    if (ri->data) {
	int n = ri->data->count;

	while (--n >= 0) {

	    switch (ri->data->what[n]) {
	    case 'a':
	    case 'r':
	    case 's':
	    case 'S':
	    case 'u':
		SvREFCNT_dec(MUTABLE_SV(ri->data->data[n]));
		break;
	    case 'f':
		Safefree(ri->data->data[n]);
		break;
	    case 'l':
	    case 'L':
	        break;
            case 'T':
                {

                    U32 refcount;
                    reg_ac_data *aho=(reg_ac_data*)ri->data->data[n];
                    OP_REFCNT_LOCK;
                    refcount = --aho->refcount;
                    OP_REFCNT_UNLOCK;
                    if ( !refcount ) {
                        PerlMemShared_free(aho->states);
                        PerlMemShared_free(aho->fail);

                        PerlMemShared_free(ri->data->data[n]);
                        PerlMemShared_free(ri->regstclass);
                    }
                }
                break;
	    case 't':
	        {

	            U32 refcount;
	            reg_trie_data *trie=(reg_trie_data*)ri->data->data[n];
                    OP_REFCNT_LOCK;
                    refcount = --trie->refcount;
                    OP_REFCNT_UNLOCK;
                    if ( !refcount ) {
                        PerlMemShared_free(trie->charmap);
                        PerlMemShared_free(trie->states);
                        PerlMemShared_free(trie->trans);
                        if (trie->bitmap)
                            PerlMemShared_free(trie->bitmap);
                        if (trie->jump)
                            PerlMemShared_free(trie->jump);
			PerlMemShared_free(trie->wordinfo);

                        PerlMemShared_free(ri->data->data[n]);
		    }
		}
		break;
	    default:
		Perl_croak(aTHX_ "panic: regfree data code '%c'", ri->data->what[n]);
	    }
	}
	Safefree(ri->data->what);
	Safefree(ri->data);
    }

    Safefree(ri);
}
