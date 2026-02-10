Perl_pad_compname_type(pTHX_ const PADOFFSET po)
{
    dVAR;
    SV* const * const av = av_fetch(PL_comppad_name, po, FALSE);
    if ( SvPAD_TYPED(*av) ) {
        return SvSTASH(*av);
    }
    return NULL;
}
