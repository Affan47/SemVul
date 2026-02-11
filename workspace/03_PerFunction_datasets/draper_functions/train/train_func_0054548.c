get_flags(const dns_rpz_cidr_key_t *ip, dns_rpz_cidr_bits_t prefix,
	dns_rpz_type_t rpz_type)
{
	if (rpz_type == DNS_RPZ_TYPE_NSIP) {
		if (prefix >= 96 &&
		    ip->w[0] == 0 && ip->w[1] == 0 &&
		    ip->w[2] == ADDR_V4MAPPED)
			return (DNS_RPZ_CIDR_FG_NSIP_DATA |
				DNS_RPZ_CIDR_FG_NSIPv4);
		else
			return (DNS_RPZ_CIDR_FG_NSIP_DATA |
				DNS_RPZ_CIDR_FG_NSIPv6);
	} else {
		return (DNS_RPZ_CIDR_FG_IP | DNS_RPZ_CIDR_FG_IP_DATA);
	}
}
