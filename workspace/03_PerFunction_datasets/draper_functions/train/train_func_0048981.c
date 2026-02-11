globexp2(const Char * ptr,
         const Char * pattern, glob_t * pglob, int *rv, int recursion)
{
    int i;
    Char *lm, *ls;
    const Char *pe, *pm, *pl;
    Char patbuf[MAXPATHLEN + 1];

    if (pglob->gl_maxdepth > 0 && recursion > pglob->gl_maxdepth) {
        errno = 0;
        return 0;
    }

    for (lm = patbuf, pm = pattern; pm != ptr; *lm++ = *pm++);
    *lm = EOS;
    ls = lm;


    for (i = 0, pe = ++ptr; *pe; pe++)
        if (*pe == LBRACKET) {

            for (pm = pe++; *pe != RBRACKET && *pe != EOS; pe++);
            if (*pe == EOS) {


                pe = pm;
            }
        } else if (*pe == LBRACE) {
            i++;
        } else if (*pe == RBRACE) {
            if (i == 0)
                break;
            i--;
        }


    if (i != 0 || *pe == EOS) {
        *rv = glob0(patbuf, pglob);
        return 0;
    }

    for (i = 0, pl = pm = ptr; pm <= pe; pm++) {
        switch (*pm) {
        case LBRACKET:

            for (pl = pm++; *pm != RBRACKET && *pm != EOS; pm++);
            if (*pm == EOS) {


                pm = pl;
            }
            break;

        case LBRACE:
            i++;
            break;

        case RBRACE:
            if (i) {
                i--;
                break;
            }

        case COMMA:
            if (i && *pm == COMMA)
                break;
            else {

                for (lm = ls; (pl < pm); *lm++ = *pl++);


                for (pl = pe + 1; (*lm++ = *pl++) != EOS;);


                *rv = globexp1(patbuf, pglob, recursion + 1);


                pl = pm + 1;
            }
            break;

        default:
            break;
        }
    }
    *rv = 0;
    return 0;
}
