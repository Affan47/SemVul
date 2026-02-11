print_rr_list_abbr(FILE *fp, ldns_rr_list *rrlist, const char *usr)
{
	size_t i;
	ldns_rr_type tp;

	for(i = 0; i < ldns_rr_list_rr_count(rrlist); i++) {
		tp = ldns_rr_get_type(ldns_rr_list_rr(rrlist, i));
		if (i == 0 && tp != LDNS_RR_TYPE_RRSIG) {
			if (usr) {
				fprintf(fp, "%s ", usr);
			}
		}
		switch(tp) {
		case LDNS_RR_TYPE_DNSKEY:
			print_dnskey_abbr(fp, ldns_rr_list_rr(rrlist, i));
			break;
		case LDNS_RR_TYPE_RRSIG:
			print_rrsig_abbr(fp, ldns_rr_list_rr(rrlist, i));
			break;
		case LDNS_RR_TYPE_DS:
			print_ds_abbr(fp, ldns_rr_list_rr(rrlist, i));
			break;
		default:

			break;
		}
		fputs("\n", fp);
	}
}
