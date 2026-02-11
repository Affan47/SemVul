macro_transform(ScmObj self, ScmObj form, ScmObj env,
                              void *data)
{
    ScmObj proc = SCM_OBJ(data);
    SCM_ASSERT(SCM_SYNTACTIC_CLOSURE_P(form));
    return Scm_ApplyRec(proc, SCM_LIST1(form));
}
