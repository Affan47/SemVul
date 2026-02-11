Scm_NanP(ScmObj obj)
{
    if (SCM_FLONUMP(obj)) {
        double v = SCM_FLONUM_VALUE(obj);
        return SCM_IS_NAN(v);
    } else if (SCM_COMPNUMP(obj)) {
        double r = SCM_COMPNUM_REAL(obj);
        double i = SCM_COMPNUM_IMAG(obj);
        return SCM_IS_NAN(r) || SCM_IS_NAN(i);
    } else if (!SCM_NUMBERP(obj)) {
        SCM_TYPE_ERROR(obj, "number");
    }
    return FALSE;
}
