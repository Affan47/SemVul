verify_dnssec_name(ldns_rdf *zone_name, ldns_dnssec_zone* zone,
		ldns_rbnode_t *cur_node, ldns_rr_list *keys)
{
	ldns_status result = LDNS_STATUS_OK;
	ldns_status status;
	ldns_dnssec_rrsets *cur_rrset;
	ldns_dnssec_name *name;
	int on_delegation_point;


	name = (ldns_dnssec_name *) cur_node->data;
	if (verbosity >= 5) {
		fprintf(myout, "Checking: ");
		ldns_rdf_print(myout, name->name);
		fprintf(myout, "\n");
	}

	if (ldns_dnssec_name_is_glue(name)) {

		cur_rrset = name->rrsets;
		while (cur_rrset) {
			if (cur_rrset->signatures) {
				if (verbosity > 0) {
					fprintf(myerr, "Error: ");
					ldns_rdf_print(myerr, name->name);
					fprintf(myerr, "\t");
					print_type(myerr, cur_rrset->type);
					fprintf(myerr, " has signature(s),"
							" but is glue\n");
				}
				result = LDNS_STATUS_ERR;
			}
			cur_rrset = cur_rrset->next;
		}
		if (name->nsec) {
			if (verbosity > 0) {
				fprintf(myerr, "Error: ");
				ldns_rdf_print(myerr, name->name);
				fprintf(myerr, " has an NSEC(3),"
						" but is glue\n");
			}
			result = LDNS_STATUS_ERR;
		}
	} else {


		on_delegation_point =
			    ldns_dnssec_rrsets_contains_type(name->rrsets,
					LDNS_RR_TYPE_NS)
			&& !ldns_dnssec_rrsets_contains_type(name->rrsets,
					LDNS_RR_TYPE_SOA);
		cur_rrset = name->rrsets;
		while(cur_rrset) {


			if ((on_delegation_point &&
			     (cur_rrset->type == LDNS_RR_TYPE_NS ||
			      cur_rrset->type == LDNS_RR_TYPE_DS)) ||
			    (!on_delegation_point &&
			     cur_rrset->type != LDNS_RR_TYPE_RRSIG &&
			     cur_rrset->type != LDNS_RR_TYPE_NSEC)) {

				status = verify_dnssec_rrset(zone_name,
						name->name, cur_rrset, keys);
				update_error(&result, status);
			}
			cur_rrset = cur_rrset->next;
		}
		status = verify_nsec(zone, cur_node, keys);
		update_error(&result, status);
	}
	return result;
}
