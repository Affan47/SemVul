method_generic_set(ScmMethod *m, ScmObj val)
{
    if (SCM_GENERICP(val))
        m->generic = SCM_GENERIC(val);
    else
        Scm_Error("generic function required, but got %S", val);
}
