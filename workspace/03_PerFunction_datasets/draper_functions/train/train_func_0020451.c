ipsec_decode_id(char *buf, size_t size, u_int8_t *id, size_t id_len,
    int isakmpform)
{
	int             id_type;
	char           *addr = 0, *mask = 0;
	u_int32_t      *idp;

	if (id) {
		if (!isakmpform) {


			id -= ISAKMP_GEN_SZ;
			id_len += ISAKMP_GEN_SZ;
		}
		id_type = GET_ISAKMP_ID_TYPE(id);
		idp = (u_int32_t *) (id + ISAKMP_ID_DATA_OFF);
		switch (id_type) {
		case IPSEC_ID_IPV4_ADDR:
			util_ntoa(&addr, AF_INET, id + ISAKMP_ID_DATA_OFF);
			snprintf(buf, size, "%08x: %s",
			    decode_32(id + ISAKMP_ID_DATA_OFF), addr);
			break;

		case IPSEC_ID_IPV4_ADDR_SUBNET:
			util_ntoa(&addr, AF_INET, id + ISAKMP_ID_DATA_OFF);
			util_ntoa(&mask, AF_INET, id + ISAKMP_ID_DATA_OFF + 4);
			snprintf(buf, size, "%08x/%08x: %s/%s",
			    decode_32(id + ISAKMP_ID_DATA_OFF),
			decode_32(id + ISAKMP_ID_DATA_OFF + 4), addr, mask);
			break;

		case IPSEC_ID_IPV6_ADDR:
			util_ntoa(&addr, AF_INET6, id + ISAKMP_ID_DATA_OFF);
			snprintf(buf, size, "%08x%08x%08x%08x: %s", *idp,
			    *(idp + 1), *(idp + 2), *(idp + 3), addr);
			break;

		case IPSEC_ID_IPV6_ADDR_SUBNET:
			util_ntoa(&addr, AF_INET6, id + ISAKMP_ID_DATA_OFF);
			util_ntoa(&mask, AF_INET6, id + ISAKMP_ID_DATA_OFF +
			    sizeof(struct in6_addr));
			snprintf(buf, size,
			    "%08x%08x%08x%08x/%08x%08x%08x%08x: %s/%s", *idp,
			    *(idp + 1), *(idp + 2), *(idp + 3), *(idp + 4),
			    *(idp + 5), *(idp + 6), *(idp + 7), addr, mask);
			break;

		case IPSEC_ID_FQDN:
		case IPSEC_ID_USER_FQDN:

			id_len -= ISAKMP_ID_DATA_OFF;
			id_len = MIN(id_len, size - 1);
			memcpy(buf, id + ISAKMP_ID_DATA_OFF, id_len);
			buf[id_len] = '\0';
			break;

#ifdef USE_X509
		case IPSEC_ID_DER_ASN1_DN:
			addr = x509_DN_string(id + ISAKMP_ID_DATA_OFF,
			    id_len - ISAKMP_ID_DATA_OFF);
			if (!addr) {
				snprintf(buf, size, "unparsable ASN1 DN ID");
				return;
			}
			strlcpy(buf, addr, size);
			break;
#endif

		default:
			snprintf(buf, size, "<id type unknown: %x>", id_type);
			break;
		}
	} else
		snprintf(buf, size, "<no ipsec id>");
	if (addr)
		free(addr);
	if (mask)
		free(mask);
}
