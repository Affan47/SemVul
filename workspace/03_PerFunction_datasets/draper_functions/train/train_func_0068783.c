Scm_StringPointerSet(ScmStringPointer *sp, int index)
{
    if (index < 0) goto badindex;
    if (sp->length < 0 || sp->size == sp->length) {
        if (index > sp->size) goto badindex;
        sp->index = index;
        sp->current = sp->start + index;
    } else {
        if (index > sp->length) goto badindex;
        sp->index = index;
        sp->current = forward_pos(sp->start, index);
    }
    return SCM_OBJ(sp);
  badindex:
    Scm_Error("index out of range: %d", index);
    return SCM_UNDEFINED;
}
