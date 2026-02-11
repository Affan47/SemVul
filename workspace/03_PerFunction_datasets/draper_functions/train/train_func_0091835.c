libnet_build_asn1_sequence(u_char *data, int *datalen, u_char type, int len)
{
    *datalen -= 4;
    if (*datalen < 0)
    {
        *datalen += 4;
        return (NULL);
    }
    *data++ = type;
    *data++ = (u_char)(0x02 | ASN_LONG_LEN);
    *data++ = (u_char)((len >> 8) & 0xFF);
    *data++ = (u_char)(len & 0xFF);
    return (data);
}
