Scm_MakeVector(int size, ScmObj fill)
{
    int i;
    ScmVector *v;
    if (size < 0) {
        Scm_Error("vector size must be a positive integer, but got %d", size);
    }
    v = make_vector(size);
    if (SCM_UNBOUNDP(fill)) fill = SCM_UNDEFINED;
    for (i=0; i<size; i++) v->elements[i] = fill;
    return SCM_OBJ(v);
}
