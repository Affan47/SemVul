log_where(SV *buf, int append, char *prefix, char *suffix, int show_line, int show_caller, int show_path)
{
    dTHX;
    dTHR;
    if (!buf)
        buf = sv_2mortal(newSVpv("",0));
    else if (!append)
        sv_setpv(buf,"");
    if (CopLINE(PL_curcop)) {
        COP *cop;
        dbi_caller_string(buf, PL_curcop, prefix, show_line, show_path);
        if (show_caller && (cop = dbi_caller_cop())) {
            SV *via = sv_2mortal(newSVpv("",0));
            dbi_caller_string(via, cop, prefix, show_line, show_path);
            sv_catpvf(buf, " via %s", SvPV_nolen(via));
        }
    }
    if (PL_dirty)
        sv_catpvf(buf, " during global destruction");
    if (suffix)
        sv_catpv(buf, suffix);
    return SvPVX(buf);
}
