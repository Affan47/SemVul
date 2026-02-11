stmt_variable_merge(stmt_ty *parent, stmt_ty *child)
{
    size_t          j;

    for (j = 0; j < child->mdef.nstrings; ++j)
        string_list_append_unique(&parent->mdef, child->mdef.string[j]);
    for (j = 0; j < child->cdef.nstrings; ++j)
        string_list_append_unique(&parent->cdef, child->cdef.string[j]);
    for (j = 0; j < child->ref.nstrings; ++j)
        string_list_append_unique(&parent->ref, child->ref.string[j]);
    for (j = 0; j < child->rref.nstrings; ++j)
        string_list_append_unique(&parent->rref, child->rref.string[j]);
}
