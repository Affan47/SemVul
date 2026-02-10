Perl_mro_get_linear_isa(pTHX_ HV *stash)
{
    struct mro_meta* meta;
    AV *isa;

    PERL_ARGS_ASSERT_MRO_GET_LINEAR_ISA;
    if(!SvOOK(stash))
        Perl_croak(aTHX_ "Can't linearize anonymous symbol table");

    meta = HvMROMETA(stash);
    if (!meta->mro_which)
        Perl_croak(aTHX_ "panic: invalid MRO!");
    isa = meta->mro_which->resolve(aTHX_ stash, 0);

    if (meta->mro_which != &dfs_alg) {
	SV * const namesv =
	    (HvENAME(stash)||HvNAME(stash))
	      ? newSVhek(HvENAME_HEK(stash)
			  ? HvENAME_HEK(stash)
			  : HvNAME_HEK(stash))
	      : NULL;

	if(namesv && (AvFILLp(isa) == -1 || !sv_eq(*AvARRAY(isa), namesv)))
	{
	    AV * const old = isa;
	    SV **svp;
	    SV **ovp = AvARRAY(old);
	    SV * const * const oend = ovp + AvFILLp(old) + 1;
	    isa = (AV *)sv_2mortal((SV *)newAV());
	    av_extend(isa, AvFILLp(isa) = AvFILLp(old)+1);
	    *AvARRAY(isa) = namesv;
	    svp = AvARRAY(isa)+1;
	    while (ovp < oend) *svp++ = SvREFCNT_inc(*ovp++);
	}
	else SvREFCNT_dec(namesv);
    }

    if (!meta->isa) {
	    HV *const isa_hash = newHV();

	    SV *const *svp = AvARRAY(isa);
	    SV *const *const svp_end = svp + AvFILLp(isa) + 1;
	    const HEK *canon_name = HvENAME_HEK(stash);
	    if (!canon_name) canon_name = HvNAME_HEK(stash);

	    while (svp < svp_end) {
		(void) hv_store_ent(isa_hash, *svp++, &PL_sv_undef, 0);
	    }

	    (void) hv_common(isa_hash, NULL, HEK_KEY(canon_name),
			     HEK_LEN(canon_name), HEK_FLAGS(canon_name),
			     HV_FETCH_ISSTORE, &PL_sv_undef,
			     HEK_HASH(canon_name));
	    (void) hv_store(isa_hash, "UNIVERSAL", 9, &PL_sv_undef, 0);

	    SvREADONLY_on(isa_hash);

	    meta->isa = isa_hash;
    }

    return isa;
}
