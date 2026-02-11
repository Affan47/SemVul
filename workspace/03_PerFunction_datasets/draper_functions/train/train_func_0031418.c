spif_mbuff_cmp(spif_mbuff_t self, spif_mbuff_t other)
{
    int c;

    SPIF_OBJ_COMP_CHECK_NULL(self, other);
    c = memcmp(SPIF_MBUFF_BUFF(self), SPIF_MBUFF_BUFF(other), MIN(self->len, other->len));
    return SPIF_CMP_FROM_INT(c);
}
