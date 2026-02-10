either_nan_p(ScmObj arg0, ScmObj arg1)
{
    if (SCM_FLONUMP(arg0) && SCM_IS_NAN(SCM_FLONUM_VALUE(arg0))) return TRUE;
    if (SCM_FLONUMP(arg1) && SCM_IS_NAN(SCM_FLONUM_VALUE(arg1))) return TRUE;
    return FALSE;
}
