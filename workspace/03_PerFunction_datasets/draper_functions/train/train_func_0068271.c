spif_str_find(spif_str_t self, spif_str_t other)
{
    char *tmp;

    ASSERT_RVAL(!SPIF_STR_ISNULL(self), (SPIF_CAST(stridx) -1));
    REQUIRE_RVAL(!SPIF_STR_ISNULL(other), (SPIF_CAST(stridx) -1));
    tmp = strstr(SPIF_CONST_CAST_C(char *) SPIF_STR_STR(self),
                 SPIF_CONST_CAST_C(char *) SPIF_STR_STR(other));
    if (tmp) {
        return SPIF_CAST(stridx) (SPIF_CAST(long) tmp - SPIF_CAST(long) (SPIF_STR_STR(self)));
    } else {
        return SPIF_CAST(stridx) (self->len);
    }
}
