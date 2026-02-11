dnskey_info(const uint8_t *rdata,
                        const size_t  rdata_len,
                        char          *out,
                        const size_t  out_len)
{
	const uint8_t  sep = *(rdata + 1) & 0x01;
	const uint16_t key_tag = knot_keytag(rdata, rdata_len);

	knot_lookup_table_t *alg = NULL;
	alg = knot_lookup_by_id(knot_dnssec_alg_names, *(rdata + 3));

	int ret = snprintf(out, out_len, "%s, alg = %s, id = %u ",
	                   sep ? "KSK" : "ZSK",
	                   alg ? alg->name : "UNKNOWN",
	                   key_tag );
	if (ret <= 0) {
		out[0] = '\0';
	}
}
