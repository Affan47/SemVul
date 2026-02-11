Scm_Vector4fArrayRef(const ScmVector4fArray *a, int n, ScmObj fallback)
{
    if (n < 0 || n >= SCM_VECTOR4F_ARRAY_SIZE(a)) {
        if (SCM_UNBOUNDP(fallback)) Scm_Error("index out of range");
        return fallback;
    }
    return Scm_MakeVector4fv(SCM_VECTOR4F_ARRAY_REFV(a, n));
}
