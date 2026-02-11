spif_linked_list_type(spif_linked_list_t self)
{
    ASSERT_RVAL(!SPIF_LIST_ISNULL(self), SPIF_NULL_TYPE(classname));
    return SPIF_OBJ_CLASSNAME(self);
}
