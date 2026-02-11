knot_rrset_merge_sort(knot_rrset_t *rrset1, const knot_rrset_t *rrset2,
                          int *merged_rrs, int *deleted_rrs)
{
	int result = KNOT_EOK;
	int merged = 0;
	int deleted = 0;

	for (uint16_t i = 0; i < rrset2->rdata_count; ++i) {
		result = knot_rrset_add_rr_sort_n(rrset1, rrset2, &merged,
		                                   &deleted, i);
		if (result != KNOT_EOK) {
			break;
		}
	}

	if (merged_rrs) {
		*merged_rrs = merged;
	}

	if (deleted_rrs) {
		*deleted_rrs = deleted;
	}

	return result;
}
