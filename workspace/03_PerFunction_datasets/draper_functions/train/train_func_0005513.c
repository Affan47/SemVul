__for_each_matched_rec(int verbose, struct node_rec *rec,
				  void *data, idbm_iface_op_fn *fn)
{
	struct rec_op_data op_data;
	int nr_found = 0, rc;

	memset(&op_data, 0, sizeof(struct rec_op_data));
	op_data.data = data;
	op_data.match_rec = rec;
	op_data.fn = fn;

	rc = idbm_for_each_rec(&nr_found, &op_data, rec_match_fn);
	if (rc) {
		if (verbose)
			log_error("Could not execute operation on all "
				  "records: %s", iscsi_err_to_str(rc));
	} else if (!nr_found) {
		if (verbose)
			log_error("No records found");
		rc = ISCSI_ERR_NO_OBJS_FOUND;
	}

	return rc;
}
