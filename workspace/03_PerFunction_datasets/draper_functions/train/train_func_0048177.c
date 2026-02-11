PerlFMM_mg_free(pTHX_ SV *const sv, MAGIC *const mg)
{
    fmmagic *m;
    fmmagic *md;
    PerlFMM *const state = (PerlFMM *) mg->mg_ptr;

    PERL_UNUSED_VAR(sv);
    for (m = state->magic; m; ) {
        md = m;
        m  = m->next;
        Safefree(md);
    }
    state->last = NULL;

    if (state->ext) {
        st_free_table(state->ext);
    }

    if (state->error != NULL) {
        SvREFCNT_dec(state->error);
        state->error = NULL;
    }
    Safefree(state);
    return 0;
}
