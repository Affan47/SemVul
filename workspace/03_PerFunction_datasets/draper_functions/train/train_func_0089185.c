nv_from_av(pTHX_ AV *av, int idx, NV default_nv)
{
    SV **svp = av_fetch(av, idx, 0);
    NV nv = (!svp || !SvOK(*svp)) ? default_nv : SvNV(*svp);
    return nv;
}
