spif_url_init_from_ptr(spif_url_t self, spif_charptr_t other)
{
    ASSERT_RVAL(!SPIF_URL_ISNULL(self), FALSE);
    if (!spif_str_init_from_ptr(SPIF_STR(self), other)) {
        return FALSE;
    }
    spif_obj_set_class(SPIF_OBJ(self), SPIF_CLASS_VAR(url));
    self->proto = SPIF_NULL_TYPE(str);
    self->user = SPIF_NULL_TYPE(str);
    self->passwd = SPIF_NULL_TYPE(str);
    self->host = SPIF_NULL_TYPE(str);
    self->port = SPIF_NULL_TYPE(str);
    self->path = SPIF_NULL_TYPE(str);
    self->query = SPIF_NULL_TYPE(str);
    spif_url_parse(self);
    return TRUE;
}
