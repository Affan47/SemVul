spif_url_init_from_unixaddr(spif_url_t self, spif_unixsockaddr_t unixaddr)
{
    ASSERT_RVAL(!SPIF_URL_ISNULL(self), FALSE);
    spif_str_init(SPIF_STR(self));
    spif_obj_set_class(SPIF_OBJ(self), SPIF_CLASS_VAR(url));
    self->proto = SPIF_NULL_TYPE(str);
    self->user = SPIF_NULL_TYPE(str);
    self->passwd = SPIF_NULL_TYPE(str);
    self->host = SPIF_NULL_TYPE(str);
    self->port = SPIF_NULL_TYPE(str);
    self->query = SPIF_NULL_TYPE(str);

    if (unixaddr->sun_path != NULL) {
        self->path = spif_str_new_from_ptr(SPIF_CHARPTR(unixaddr->sun_path));
    } else {
        self->path = SPIF_NULL_TYPE(str);
    }
    return TRUE;
}
