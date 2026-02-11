ib_error_decode(const ISC_STATUS *status) {
    if (status[0] == 1 && status[1] > 0)
    {
        SV *sv = NULL;
        long sqlcode;
#if !defined(FB_API_VER) || FB_API_VER < 20
        ISC_STATUS *pvector = status;
#else
        const ISC_STATUS *pvector = status;
#endif
#if defined (INCLUDE_TYPES_PUB_H)
        ISC_SCHAR msg[1024];
#else
        char msg[1024];
#endif

        if ((sqlcode = isc_sqlcode(status)) != 0)
        {
            isc_sql_interprete((short) sqlcode, msg, sizeof(msg));
            sv = sv_2mortal(newSVpv(msg, 0));
        }

#if !defined(FB_API_VER) || FB_API_VER < 20
        while (isc_interprete(msg, &pvector))
#else
        while (fb_interpret(msg, sizeof(msg), &pvector))
#endif
        {
            if ( sv != NULL ) {
                sv_catpvn(sv, "\n-", 2);
                sv_catpv(sv, msg);
            }
            else sv = sv_2mortal(newSVpv(msg,0));
        }

        sv_catpvn(sv, "\0", 1);

        return SvPV_nolen(sv);
    }
    else return NULL;
}
