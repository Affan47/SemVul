Scm_StringPointerSubstring(ScmStringPointer *sp, int afterp)
{

    if (sp->length < 0) {
        if (afterp)
            return SCM_OBJ(make_str(-1, sp->size - sp->index, sp->current, 0));
        else
            return SCM_OBJ(make_str(-1, sp->index, sp->start, 0));
    } else {
        if (afterp)
            return SCM_OBJ(make_str(sp->length - sp->index,
                                    (int)(sp->start + sp->size - sp->current),
                                    sp->current, 0));
        else
            return SCM_OBJ(make_str(sp->index,
                                    (int)(sp->current - sp->start),
                                    sp->start, 0));
    }
}
