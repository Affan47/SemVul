rc1_lex_minmax(regcomp_ctx *ctx)
{
    int rep_min = -1, rep_max = -1, exact = FALSE, ch;
    ScmObj pos, m;
    ScmObj type = SCM_SYM_REP;

    pos = Scm_PortSeekUnsafe(ctx->ipat, SCM_MAKE_INT(0), SEEK_CUR);

    for (;;) {
        ch = Scm_GetcUnsafe(ctx->ipat);
        if (SCM_CHAR_ASCII_P(ch) && isdigit(ch)) {
            if (rep_min < 0) {
                rep_min = (ch - '0');
            } else {
                rep_min = rep_min*10 + (ch - '0');
            }
        } else if (ch == ',') {


            if (rep_min < 0) rep_min = 0;
            break;
        } else if (ch == '}') {
            exact = TRUE;
            break;
        } else {
            goto bad_min_max;
        }
    }
    if (rep_min < 0) goto bad_min_max;
    if (rep_min > MAX_LIMITED_REPEAT) goto out_of_range;
    if (!exact) {
        for (;;) {
            ch = Scm_GetcUnsafe(ctx->ipat);
            if (SCM_CHAR_ASCII_P(ch) && isdigit(ch)) {
                if (rep_max < 0) {
                    rep_max = (ch - '0');
                } else {
                    rep_max = rep_max*10 + (ch - '0');
                }
            } else if (ch == '}') {
                break;
            } else {
                goto bad_min_max;
            }
        }
        if (rep_max > MAX_LIMITED_REPEAT) goto out_of_range;
        if (rep_max >= 0 && rep_max < rep_min) {
            Scm_Error("{n,m}-syntax requires n <= m: %S", ctx->pattern);
        }
    }

    if (exact)            m = SCM_MAKE_INT(rep_min);
    else if (rep_max < 0) m = SCM_FALSE;
    else                  m = SCM_MAKE_INT(rep_max);

    ch = Scm_GetcUnsafe(ctx->ipat);
    if (ch == '?') type = SCM_SYM_REP_MIN;
    else Scm_UngetcUnsafe(ch, ctx->ipat);
    return Scm_Cons(type, Scm_Cons(SCM_MAKE_INT(rep_min), m));

  out_of_range:
    Scm_Error("{n,m}-syntax can accept up to %d count: %S",
              MAX_LIMITED_REPEAT, ctx->pattern);

  bad_min_max:

    Scm_PortSeekUnsafe(ctx->ipat, pos, SEEK_SET);
    return SCM_MAKE_CHAR('{');
}
