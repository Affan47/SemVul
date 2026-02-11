spif_str_substr(spif_str_t self, spif_stridx_t idx, spif_stridx_t cnt)
{
    ASSERT_RVAL(!SPIF_STR_ISNULL(self), SPIF_NULL_TYPE(str));
    if (idx < 0) {
        idx = self->len + idx;
    }
    REQUIRE_RVAL(idx >= 0, SPIF_NULL_TYPE(str));
    REQUIRE_RVAL(idx < self->len, SPIF_NULL_TYPE(str));
    if (cnt <= 0) {
        cnt = self->len - idx + cnt;
    }
    REQUIRE_RVAL(cnt >= 0, SPIF_NULL_TYPE(str));
    UPPER_BOUND(cnt, self->len - idx);
    return spif_str_new_from_buff(SPIF_STR_STR(self) + idx, cnt);
}
