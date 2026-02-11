Scm_S16VectorFill(ScmS16Vector *vec, short fill, int start, int end)
{
    int i, size = SCM_S16VECTOR_SIZE(vec);
    SCM_CHECK_START_END(start, end, size);
    SCM_UVECTOR_CHECK_MUTABLE(vec);
    for (i=start; i<end; i++) SCM_S16VECTOR_ELEMENTS(vec)[i] = fill;
    return SCM_OBJ(vec);
}
