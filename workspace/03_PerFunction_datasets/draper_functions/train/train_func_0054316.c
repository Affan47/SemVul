istgt_lu_disk_check_pr(ISTGT_LU_DISK *spec, CONN_Ptr conn, int pr_allow)
{
	ISTGT_LU_PR_KEY *prkey;

#ifdef ISTGT_TRACE_DISK
	ISTGT_TRACELOG(ISTGT_TRACE_DEBUG,
	    "RSV_KEY=0x%16.16"PRIx64", RSV_TYPE=0x%x, PR_ALLOW=0x%x\n",
	    spec->rsv_key, spec->rsv_type, pr_allow);
#endif

	prkey = istgt_lu_disk_find_pr_key(spec, conn->initiator_port,
	    conn->target_port, 0);
	if (prkey != NULL) {
#ifdef ISTGT_TRACE_DISK
		ISTGT_TRACELOG(ISTGT_TRACE_DEBUG,
		    "PRKEY(0x%16.16"PRIx64") found for %s\n",
		    prkey->key, conn->initiator_port);
#endif

		if (spec->rsv_key == prkey->key) {

			return 0;
		}

		switch (spec->rsv_type) {
		case ISTGT_LU_PR_TYPE_WRITE_EXCLUSIVE_ALL_REGISTRANTS:
			if (pr_allow & PR_ALLOW_ALLRR)
				return 0;
			return -1;
		case ISTGT_LU_PR_TYPE_EXCLUSIVE_ACCESS_ALL_REGISTRANTS:
			if (pr_allow & PR_ALLOW_ALLRR)
				return 0;
			return -1;
		case ISTGT_LU_PR_TYPE_WRITE_EXCLUSIVE_REGISTRANTS_ONLY:
			if (pr_allow & PR_ALLOW_ALLRR)
				return 0;
			return -1;
		case ISTGT_LU_PR_TYPE_EXCLUSIVE_ACCESS_REGISTRANTS_ONLY:
			if (pr_allow & PR_ALLOW_ALLRR)
				return 0;
			return -1;
		}
	} else {
#ifdef ISTGT_TRACE_DISK
		ISTGT_TRACELOG(ISTGT_TRACE_DEBUG,
		    "PRKEY not found for %s\n",
		    conn->initiator_port);
#endif

		switch (spec->rsv_type) {
		case ISTGT_LU_PR_TYPE_WRITE_EXCLUSIVE_ALL_REGISTRANTS:
			if (pr_allow & PR_ALLOW_WERR)
				return 0;
			return -1;
		case ISTGT_LU_PR_TYPE_WRITE_EXCLUSIVE_REGISTRANTS_ONLY:
			if (pr_allow & PR_ALLOW_WERR)
				return 0;
			return -1;
		case ISTGT_LU_PR_TYPE_EXCLUSIVE_ACCESS_ALL_REGISTRANTS:
			if (pr_allow & PR_ALLOW_EARR)
				return 0;
			return -1;
		case ISTGT_LU_PR_TYPE_EXCLUSIVE_ACCESS_REGISTRANTS_ONLY:
			if (pr_allow & PR_ALLOW_EARR)
				return 0;
			return -1;
		}
	}

#ifdef ISTGT_TRACE_DISK
	ISTGT_TRACELOG(ISTGT_TRACE_DEBUG, "non registrans type\n");
#endif

	switch (spec->rsv_type) {
	case ISTGT_LU_PR_TYPE_WRITE_EXCLUSIVE:
		if (pr_allow & PR_ALLOW_WE)
			return 0;
		return -1;
	case ISTGT_LU_PR_TYPE_EXCLUSIVE_ACCESS:
		if (pr_allow & PR_ALLOW_EA)
			return 0;
		return -1;
	}


	return -1;
}
