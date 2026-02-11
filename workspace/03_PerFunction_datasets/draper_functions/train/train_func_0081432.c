scm_make_cpointer(void *ptr)
{
    ScmObj obj;

    obj = scm_alloc_cell();
    SCM_C_POINTER_INIT(obj, ptr);
    return obj;
}
