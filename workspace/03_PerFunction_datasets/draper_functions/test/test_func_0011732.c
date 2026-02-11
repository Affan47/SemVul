spif_regexp_comp(spif_regexp_t self, spif_regexp_t other)
{
    SPIF_OBJ_COMP_CHECK_NULL(self, other);
    return spif_str_comp(SPIF_STR(self), SPIF_STR(other));
}
