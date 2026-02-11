Scm_LogIor(ScmObj x, ScmObj y)
{
    if (!SCM_INTEGERP(x)) Scm_Error("exact integer required, but got %S", x);
    if (!SCM_INTEGERP(y)) Scm_Error("exact integer required, but got %S", y);
    if (SCM_INTP(x)) {
        if (SCM_INTP(y))
            return SCM_MAKE_INT(SCM_INT_VALUE(x) | SCM_INT_VALUE(y));
        else
            x = Scm_MakeBignumFromSI(SCM_INT_VALUE(x));
    } else {
        if (SCM_INTP(y)) y = Scm_MakeBignumFromSI(SCM_INT_VALUE(y));
    }
    return Scm_BignumLogIor(SCM_BIGNUM(x), SCM_BIGNUM(y));
}
