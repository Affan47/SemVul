Protocol_CRITFAIL(PROTO_PARMS) {

	unsigned long int cf_lnum = (unsigned long int) data;
	unsigned int cf_num = (unsigned int) cf_lnum;

	if (cf_num >= globalreg->critfail_vec.size())
		cf_num = 0;

	string scratch;

	cache->Filled(field_vec->size());

	for (unsigned int x = 0; x < field_vec->size(); x++) {
		unsigned int fnum = (*field_vec)[x];
		if (fnum >= CRITFAIL_maxfield) {
			out_string += "Unknown field requested.";
			return -1;
		}

		if (cache->Filled(fnum)) {
			out_string += cache->GetCache(fnum) + " ";
			continue;
		}

		switch (fnum) {
			case CRITFAIL_id:
				scratch = IntToString(cf_num);
				break;
			case CRITFAIL_time:
				scratch = IntToString(globalreg->critfail_vec[cf_num].fail_time);
				break;
			case CRITFAIL_message:
				scratch = "\001" + globalreg->critfail_vec[cf_num].fail_msg + "\001";
				break;
		}

		out_string += scratch;
		cache->Cache(fnum, scratch);

		out_string += " ";
	}

	return 1;
}
