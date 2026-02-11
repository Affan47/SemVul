format_sexp(ScmPort *out, ScmObj arg,
                        ScmObj *params, int nparams,
                        int rightalign, int dots, int mode)
{
    int mincol = 0, colinc = 1, minpad = 0, maxcol = -1, nwritten = 0, i;
    ScmChar padchar = ' ';
    ScmObj tmpout = Scm_MakeOutputStringPort(TRUE);
    ScmString *tmpstr;

    if (nparams>0 && SCM_INTP(params[0])) mincol = SCM_INT_VALUE(params[0]);
    if (nparams>1 && SCM_INTP(params[1])) colinc = SCM_INT_VALUE(params[1]);
    if (nparams>2 && SCM_INTP(params[2])) minpad = SCM_INT_VALUE(params[2]);
    if (nparams>3 && SCM_CHARP(params[3])) padchar = SCM_CHAR_VALUE(params[3]);
    if (nparams>4 && SCM_INTP(params[4])) maxcol = SCM_INT_VALUE(params[4]);

    if (minpad > 0 && rightalign) {
        for (i=0; i<minpad; i++) Scm_PutcUnsafe(padchar, SCM_PORT(tmpout));
    }
    if (maxcol > 0) {
        nwritten = Scm_WriteLimited(arg, tmpout, mode, maxcol);
    } else {
        Scm_Write(arg, tmpout, mode);
    }
    if (minpad > 0 && !rightalign) {
        for (i=0; i<minpad; i++) Scm_PutcUnsafe(padchar, SCM_PORT(tmpout));
    }
    tmpstr = SCM_STRING(Scm_GetOutputString(SCM_PORT(tmpout), 0));

    if (maxcol > 0 && nwritten < 0) {
        const char *s = Scm_GetStringContent(tmpstr, NULL, NULL, NULL), *e;
        if (dots && maxcol > 4) {
            e = Scm_StringBodyPosition(SCM_STRING_BODY(tmpstr), maxcol-4);
            Scm_PutzUnsafe(s, (int)(e-s), out);
            Scm_PutzUnsafe(" ...", 4, out);
        } else {
            e = Scm_StringBodyPosition(SCM_STRING_BODY(tmpstr), maxcol);
            Scm_PutzUnsafe(s, (int)(e-s), out);
        }
    } else {
        format_pad(out, tmpstr, mincol, colinc, padchar, rightalign);
    }
}
