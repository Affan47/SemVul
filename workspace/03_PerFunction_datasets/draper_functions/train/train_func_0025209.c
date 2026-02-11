spif_linked_list_vector_find(spif_linked_list_t self, spif_obj_t obj)
{
    spif_linked_list_item_t current;

    ASSERT_RVAL(!SPIF_VECTOR_ISNULL(self), SPIF_NULL_TYPE(obj));
    REQUIRE_RVAL(!SPIF_OBJ_ISNULL(obj), SPIF_NULL_TYPE(obj));
    for (current = self->head; current; current = current->next) {
        spif_cmp_t c;


        ASSERT_RVAL(!SPIF_OBJ_ISNULL(current->data), SPIF_NULL_TYPE(obj));
        c = SPIF_OBJ_COMP(current->data, obj);
        if (SPIF_CMP_IS_EQUAL(c)) {
            return current->data;
        } else if (SPIF_CMP_IS_GREATER(c)) {
            break;
        }
    }
    return SPIF_NULL_TYPE(obj);
}
