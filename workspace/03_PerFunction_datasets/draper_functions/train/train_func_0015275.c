fmm_bufmagic(PerlFMM *state, unsigned char **buffer, char **mime_type)
{
    if (fmm_softmagic(state, buffer, HOWMANY, mime_type) == 0) {
#ifdef FMM_DEBUG
    PerlIO_printf(PerlIO_stderr(), "[fmm_bufmagic]: fmm_softmagic returns 0\n");
#endif
        return 0;
    }

    if (fmm_ascmagic(*buffer, HOWMANY, mime_type) == 0) {
#ifdef FMM_DEBUG
    PerlIO_printf(PerlIO_stder(), "[fmm_bufmagic]: fmm_ascmagic returns 0\n");
#endif
        return 0;
    }
    return 1;
}
