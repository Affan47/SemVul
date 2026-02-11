str2bigint(char *num)
{
    int count;
    SV *rv;
    dSP;

    ENTER;
    SAVETMPS;

    load_Math_BigInt();
    SPAGAIN;

    EXTEND(SP, 2);
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv("Math::BigInt", 0)));
    XPUSHs(sv_2mortal(newSVpv(num, 0)));
    PUTBACK;

    count = call_method("new", G_SCALAR);

    SPAGAIN;

    if (count != 1)
	croak("Expected a result from Math::Bigint->new");

    rv = POPs;
    SvREFCNT_inc(rv);

    PUTBACK;
    FREETMPS;
    LEAVE;

    return rv;
}
