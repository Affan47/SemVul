Scm_U8VectorCopyX(ScmU8Vector *dst,
                           int dstart,
                           ScmU8Vector *src,
                           int sstart,
                           int send)
{
    int dlen = SCM_U8VECTOR_SIZE(dst);
    int slen = SCM_U8VECTOR_SIZE(src);
    int size;

    SCM_UVECTOR_CHECK_MUTABLE(dst);
    SCM_CHECK_START_END(sstart, send, slen);

    if (dstart < 0 || dstart >= dlen) return SCM_OBJ(dst);
    if (dlen - dstart > send - sstart)  size = send - sstart;
    else size = dlen - dstart;

    memmove(SCM_U8VECTOR_ELEMENTS(dst) + dstart,
            SCM_U8VECTOR_ELEMENTS(src) + sstart,
            size * sizeof(unsigned char));
    return SCM_OBJ(dst);
}
