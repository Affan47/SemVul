Perl_do_kv(pTHX)
{
    dVAR;
    dSP;
    HV * const keys = MUTABLE_HV(POPs);
    HE *entry;
    const I32 gimme = GIMME_V;
    const I32 dokv =     (PL_op->op_type == OP_RV2HV || PL_op->op_type == OP_PADHV);

    const I32 dokeys =   dokv || (PL_op->op_type == OP_KEYS || PL_op->op_type == OP_RKEYS);
    const I32 dovalues = dokv || (PL_op->op_type == OP_VALUES || PL_op->op_type == OP_RVALUES);

    (void)hv_iterinit(keys);

    if (gimme == G_VOID)
	RETURN;

    if (gimme == G_SCALAR) {
	if (PL_op->op_flags & OPf_MOD || LVRET) {
	    SV * const ret = sv_2mortal(newSV_type(SVt_PVLV));
	    sv_magic(ret, NULL, PERL_MAGIC_nkeys, NULL, 0);
	    LvTYPE(ret) = 'k';
	    LvTARG(ret) = SvREFCNT_inc_simple(keys);
	    PUSHs(ret);
	}
	else {
	    IV i;
	    dTARGET;

	    if (! SvTIED_mg((const SV *)keys, PERL_MAGIC_tied) ) {
		i = HvUSEDKEYS(keys);
	    }
	    else {
		i = 0;
		while (hv_iternext(keys)) i++;
	    }
	    PUSHi( i );
	}
	RETURN;
    }

    EXTEND(SP, HvUSEDKEYS(keys) * (dokeys + dovalues));

    PUTBACK;
    while ((entry = hv_iternext(keys))) {
	SPAGAIN;
	if (dokeys) {
	    SV* const sv = hv_iterkeysv(entry);
	    XPUSHs(sv);
	}
	if (dovalues) {
	    SV *tmpstr;
	    PUTBACK;
	    tmpstr = hv_iterval(keys,entry);
	    DEBUG_H(Perl_sv_setpvf(aTHX_ tmpstr, "%lu%%%d=%lu",
			    (unsigned long)HeHASH(entry),
			    (int)HvMAX(keys)+1,
			    (unsigned long)(HeHASH(entry) & HvMAX(keys))));
	    SPAGAIN;
	    XPUSHs(tmpstr);
	}
	PUTBACK;
    }
    return NORMAL;
}
