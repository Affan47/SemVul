ptr_struct_mark(enum_ptr_t *pep, gc_state_t * ignored)
{
    obj_header_t *ptr = (obj_header_t *)pep->ptr;

    if (ptr == 0)
        return false;
    ptr--;
    if (!o_is_unmarked(ptr))
        return false;
    o_mark(ptr);
    return true;
}
