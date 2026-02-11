spif_url_done(spif_url_t self)
{
    ASSERT_RVAL(!SPIF_URL_ISNULL(self), FALSE);
    if (!SPIF_STR_ISNULL(self->proto)) {
        spif_str_del(self->proto);
        self->proto = SPIF_NULL_TYPE(str);
    }
    if (!SPIF_STR_ISNULL(self->user)) {
        spif_str_del(self->user);
        self->user = SPIF_NULL_TYPE(str);
    }
    if (!SPIF_STR_ISNULL(self->passwd)) {
        spif_str_del(self->passwd);
        self->passwd = SPIF_NULL_TYPE(str);
    }
    if (!SPIF_STR_ISNULL(self->host)) {
        spif_str_del(self->host);
        self->host = SPIF_NULL_TYPE(str);
    }
    if (!SPIF_STR_ISNULL(self->port)) {
        spif_str_del(self->port);
        self->port = SPIF_NULL_TYPE(str);
    }
    if (!SPIF_STR_ISNULL(self->path)) {
        spif_str_del(self->path);
        self->path = SPIF_NULL_TYPE(str);
    }
    if (!SPIF_STR_ISNULL(self->query)) {
        spif_str_del(self->query);
        self->query = SPIF_NULL_TYPE(str);
    }
    spif_str_done(SPIF_STR(self));
    return TRUE;
}
