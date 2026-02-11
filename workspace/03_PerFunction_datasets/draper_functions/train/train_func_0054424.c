S_incpush(pTHX_ const char *const dir, STRLEN len, U32 flags)
{
    dVAR;
#ifndef PERL_IS_MINIPERL
    const U8 using_sub_dirs
	= (U8)flags & (INCPUSH_ADD_VERSIONED_SUB_DIRS
		       |INCPUSH_ADD_ARCHONLY_SUB_DIRS|INCPUSH_ADD_OLD_VERS);
    const U8 add_versioned_sub_dirs
	= (U8)flags & INCPUSH_ADD_VERSIONED_SUB_DIRS;
    const U8 add_archonly_sub_dirs
	= (U8)flags & INCPUSH_ADD_ARCHONLY_SUB_DIRS;
#ifdef PERL_INC_VERSION_LIST
    const U8 addoldvers  = (U8)flags & INCPUSH_ADD_OLD_VERS;
#endif
#endif
    const U8 unshift     = (U8)flags & INCPUSH_UNSHIFT;
    const U8 push_basedir = (flags & INCPUSH_NOT_BASEDIR) ? 0 : 1;
    AV *const inc = GvAVn(PL_incgv);

    PERL_ARGS_ASSERT_INCPUSH;
    assert(len > 0);


    {
	SV *const libdir = mayberelocate(dir, len, flags);


#ifndef PERL_IS_MINIPERL
	AV *const av = (using_sub_dirs) ? (unshift ? newAV() : inc) : NULL;


	if (using_sub_dirs) {
	    SV *subdir = newSVsv(libdir);
#ifdef PERL_INC_VERSION_LIST

	    const char * const incverlist[] = { PERL_INC_VERSION_LIST };
	    const char * const *incver;
#endif

	    if (add_versioned_sub_dirs) {

		sv_catpvs(subdir, "/" PERL_FS_VERSION "/" ARCHNAME);
		subdir = S_incpush_if_exists(aTHX_ av, subdir, libdir);


		sv_catpvs(subdir, "/" PERL_FS_VERSION);
		subdir = S_incpush_if_exists(aTHX_ av, subdir, libdir);
	    }

#ifdef PERL_INC_VERSION_LIST
	    if (addoldvers) {
		for (incver = incverlist; *incver; incver++) {

		    Perl_sv_catpvf(aTHX_ subdir, "/%s", *incver);
		    subdir = S_incpush_if_exists(aTHX_ av, subdir, libdir);
		}
	    }
#endif

	    if (add_archonly_sub_dirs) {

		sv_catpvs(subdir, "/" ARCHNAME);
		subdir = S_incpush_if_exists(aTHX_ av, subdir, libdir);

	    }

	    assert (SvREFCNT(subdir) == 1);
	    SvREFCNT_dec(subdir);
	}
#endif

	if (unshift) {
#ifdef PERL_IS_MINIPERL
	    const U32 extra = 0;
#else
	    U32 extra = av_len(av) + 1;
#endif
	    av_unshift(inc, extra + push_basedir);
	    if (push_basedir)
		av_store(inc, extra, libdir);
#ifndef PERL_IS_MINIPERL
	    while (extra--) {


		av_store(inc, extra, SvREFCNT_inc(*av_fetch(av, extra, FALSE)));
	    }
	    SvREFCNT_dec(av);
#endif
	}
	else if (push_basedir) {
	    av_push(inc, libdir);
	}

	if (!push_basedir) {
	    assert (SvREFCNT(libdir) == 1);
	    SvREFCNT_dec(libdir);
	}
    }
}
