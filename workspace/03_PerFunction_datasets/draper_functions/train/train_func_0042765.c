class_array_to_names(ScmClass **array, int len)
{
    ScmObj h = SCM_NIL, t = SCM_NIL;
    int i;
    for (i=0; i<len; i++, array++) SCM_APPEND1(h, t, (*array)->name);
    return h;
}
