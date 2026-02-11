of10_table_stats_reply_print(const u_char *cp, const u_char *ep, u_int len) {
	const u_char *cp0 = cp;
	const u_int len0 = len;

	while (len) {
		if (len < OF_TABLE_STATS_LEN)
			goto corrupt;

		TCHECK2(*cp, 1);
		printf("\n\t table_id %s", tok2str(tableid_str, "%u", *cp));
		cp += 1;

		TCHECK2(*cp, 3);
		cp += 3;

		TCHECK2(*cp, OFP_MAX_TABLE_NAME_LEN);
		printf(", name '");
		fn_print(cp, cp + OFP_MAX_TABLE_NAME_LEN);
		printf("'");
		cp += OFP_MAX_TABLE_NAME_LEN;

		TCHECK2(*cp, 4);
		printf("\n\t  wildcards 0x%08x", EXTRACT_32BITS(cp));
		of10_bitmap_print(ofpfw_bm, EXTRACT_32BITS(cp), OFPFW_U);
		cp += 4;

		TCHECK2(*cp, 4);
		printf("\n\t  max_entries %u", EXTRACT_32BITS(cp));
		cp += 4;

		TCHECK2(*cp, 4);
		printf(", active_count %u", EXTRACT_32BITS(cp));
		cp += 4;

		TCHECK2(*cp, 8);
		printf(", lookup_count %" PRIu64, EXTRACT_64BITS(cp));
		cp += 8;

		TCHECK2(*cp, 8);
		printf(", matched_count %" PRIu64, EXTRACT_64BITS(cp));
		cp += 8;

		len -= OF_TABLE_STATS_LEN;
	}
	return cp;

corrupt:
	printf(" (corrupt)");
	TCHECK2(*cp0, len0);
	return cp0 + len0;
trunc:
	printf(" [|openflow]");
	return ep;
}
