heim_ntlm_encode_type1(const struct ntlm_type1 *type1, struct ntlm_buf *data)
{
    krb5_error_code ret;
    struct sec_buffer domain, hostname;
    krb5_storage *out;
    uint32_t base, flags;
    int ucs2 = 0;

    flags = type1->flags;
    base = 16;

    if (flags & NTLM_NEG_UNICODE)
	ucs2 = 1;

    if (type1->domain) {
	base += SIZE_SEC_BUFFER;
	flags |= NTLM_OEM_SUPPLIED_DOMAIN;
    }
    if (type1->hostname) {
	base += SIZE_SEC_BUFFER;
	flags |= NTLM_OEM_SUPPLIED_WORKSTATION;
    }
    if (flags & NTLM_NEG_VERSION)
	base += SIZE_OS_VERSION;

    if (type1->domain) {
	domain.offset = base;
	domain.length = len_string(ucs2, type1->domain);
	domain.allocated = domain.length;
    } else {
	domain.offset = 0;
	domain.length = 0;
	domain.allocated = 0;
    }

    if (type1->hostname) {
	hostname.offset = domain.allocated + domain.offset;
	hostname.length = len_string(ucs2, type1->hostname);
	hostname.allocated = hostname.length;
    } else {
	hostname.offset = 0;
	hostname.length = 0;
	hostname.allocated = 0;
    }

    out = krb5_storage_emem();
    if (out == NULL)
	return ENOMEM;

    krb5_storage_set_byteorder(out, KRB5_STORAGE_BYTEORDER_LE);
    CHECK_SIZE(krb5_storage_write(out, ntlmsigature, sizeof(ntlmsigature)),
	  sizeof(ntlmsigature));
    CHECK(krb5_store_uint32(out, 1), 0);
    CHECK(krb5_store_uint32(out, flags), 0);

    CHECK(store_sec_buffer(out, &domain), 0);
    CHECK(store_sec_buffer(out, &hostname), 0);

    if (flags & NTLM_NEG_VERSION) {
	CHECK(encode_os_version(out), 0);
    }
    if (type1->domain)
	CHECK(put_string(out, ucs2, type1->domain), 0);
    if (type1->hostname)
	CHECK(put_string(out, ucs2, type1->hostname), 0);

    {
	krb5_data d;
	ret = krb5_storage_to_data(out, &d);
	data->data = d.data;
	data->length = d.length;
    }
out:
    krb5_storage_free(out);

    return ret;
}
