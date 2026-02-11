Scm_MakeFillString(int len, ScmChar fill)
{
    int size = SCM_CHAR_NBYTES(fill), i;
    char *ptr = SCM_NEW_ATOMIC2(char *, size*len+1);
    char *p;

    if (len < 0) Scm_Error("length out of range: %d", len);
    for (i=0, p=ptr; i<len; i++, p+=size) {
        SCM_CHAR_PUT(p, fill);
    }
    ptr[size*len] = '\0';
    return SCM_OBJ(make_str(len, size*len, ptr, SCM_STRING_TERMINATED));
}
