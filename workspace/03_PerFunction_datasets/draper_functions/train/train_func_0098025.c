Scm_GtkCallThunk(gpointer closure)
{
    ScmObj r;
    SCM_ASSERT(closure != NULL && SCM_PROCEDUREP(closure));
    r = Scm_ApplyRec2(SCM_OBJ(&callcallback_proc__STUB),
                      SCM_OBJ(closure), SCM_NIL);
    return SCM_BOOL_VALUE(r);
}
