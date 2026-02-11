spif_url_init_from_ipaddr(spif_url_t self, spif_ipsockaddr_t ipaddr)
{
    spif_uint8_t tries;
    spif_hostinfo_t hinfo;

    ASSERT_RVAL(!SPIF_URL_ISNULL(self), FALSE);
    spif_str_init(SPIF_STR(self));
    spif_obj_set_class(SPIF_OBJ(self), SPIF_CLASS_VAR(url));
    self->proto = SPIF_NULL_TYPE(str);
    self->user = SPIF_NULL_TYPE(str);
    self->passwd = SPIF_NULL_TYPE(str);
    self->path = SPIF_NULL_TYPE(str);
    self->query = SPIF_NULL_TYPE(str);


    h_errno = 0;
    tries = 0;
    do {
        tries++;
        hinfo = gethostbyaddr(SPIF_CONST_CAST_C(char *) &(ipaddr->sin_addr), sizeof(ipaddr->sin_addr), AF_INET);
    } while ((tries <= 3) && (hinfo == NULL) && (h_errno == TRY_AGAIN));
    if (hinfo == NULL || hinfo->h_name == NULL) {
        spif_charptr_t buff;

        buff = SPIF_CHARPTR(inet_ntoa(ipaddr->sin_addr));
        self->host = spif_str_new_from_ptr(buff);
    } else {
        self->host = spif_str_new_from_ptr(SPIF_CHARPTR(hinfo->h_name));
    }

    self->port = spif_str_new_from_num(ntohs(ipaddr->sin_port));
    return TRUE;
}
