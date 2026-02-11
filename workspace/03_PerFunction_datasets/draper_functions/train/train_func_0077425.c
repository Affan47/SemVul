modperl_handler_perl_add_handlers(pTHX_
                                      request_rec *r,
                                      conn_rec *c,
                                      server_rec *s,
                                      apr_pool_t *p,
                                      const char *name,
                                      SV *sv,
                                      modperl_handler_action_e action)
{
    I32 i;
    AV *av = (AV *)NULL;
    MpAV **handlers =
        modperl_handler_get_handlers(r, c, s,
                                     p, name, action);

    if (!(handlers && *handlers)) {
        return FALSE;
    }

    if (SvROK(sv) && (SvTYPE(SvRV(sv)) == SVt_PVAV)) {
        av = (AV*)SvRV(sv);

        for (i=0; i <= AvFILL(av); i++) {
            sv = *av_fetch(av, i, FALSE);
            push_sv_handler;
        }
    }
    else {
        push_sv_handler;
    }

    return TRUE;
}
