knot_rrset_add_rrsigs(knot_rrset_t *rrset, knot_rrset_t *rrsigs,
                          knot_rrset_dupl_handling_t dupl)
{
	if (rrset == NULL || rrsigs == NULL ||
	    !knot_dname_is_equal(rrset->owner, rrsigs->owner)) {
		return KNOT_EINVAL;
	}

	int rc;
	if (rrset->rrsigs != NULL) {
		if (dupl == KNOT_RRSET_DUPL_MERGE) {
			int merged, deleted_rrs;
			rc = knot_rrset_merge_sort(rrset->rrsigs, rrsigs,
			                           &merged, &deleted_rrs);
			if (rc != KNOT_EOK) {
				return rc;
			} else if (merged || deleted_rrs) {
				return 1;
			} else {
				return 0;
			}
		} else if (dupl == KNOT_RRSET_DUPL_SKIP) {
			return 2;
		} else if (dupl == KNOT_RRSET_DUPL_REPLACE) {
			rrset->rrsigs = rrsigs;
		}
	} else {
		if (rrset->ttl != rrsigs->ttl) {
			rrsigs->ttl = rrset->ttl;
		}
		rrset->rrsigs = rrsigs;
	}

	return KNOT_EOK;
}
