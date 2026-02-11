blockhook_csc_pre_end(pTHX_ OP **o)
{
    dMY_CXT;

    PERL_UNUSED_ARG(o);


    if (GvAV(MY_CXT.cscgv) == MY_CXT.cscav && MY_CXT.cscav) {
        av_clear(MY_CXT.cscav);
    }

}
