krb5_make_fulladdr(krb5_context context, krb5_address *kaddr,
                   krb5_address *kport, krb5_address *raddr)
{
    register krb5_octet * marshal;
    krb5_int32 tmp32;
    krb5_int16 tmp16;

    if ((kport == NULL) || (kport == NULL))
        return EINVAL;

    raddr->length = kaddr->length + kport->length + (4 * sizeof(krb5_int32));
    if (!(raddr->contents = (krb5_octet *)malloc(raddr->length)))
        return ENOMEM;

    raddr->addrtype = ADDRTYPE_ADDRPORT;
    marshal = raddr->contents;

    tmp16 = kaddr->addrtype;
    *marshal++ = 0x00;
    *marshal++ = 0x00;
    store_16_le(tmp16, marshal);
    marshal += 2;

    tmp32 = kaddr->length;
    store_32_le(tmp32, marshal);
    marshal += 4;

    (void) memcpy(marshal, kaddr->contents, kaddr->length);
    marshal += kaddr->length;

    tmp16 = kport->addrtype;
    *marshal++ = 0x00;
    *marshal++ = 0x00;
    store_16_le(tmp16, marshal);
    marshal += 2;

    tmp32 = kport->length;
    store_32_le(tmp32, marshal);
    marshal += 4;

    (void) memcpy(marshal, kport->contents, kport->length);
    marshal += kport->length;
    return 0;
}
