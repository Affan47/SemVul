istgt_lu_visible(ISTGT_Ptr istgt, ISTGT_LU_Ptr lu, const char *iqn, int pg_tag)
{
	INITIATOR_GROUP *igp;
	int match_pg_tag;
	int ig_tag;
	int i, j;

	if (istgt == NULL || lu == NULL || iqn == NULL)
		return 0;

	match_pg_tag = 0;
	for (i = 0; i < lu->maxmap; i++) {
		if (lu->map[i].pg_tag == pg_tag) {
			match_pg_tag = 1;
			break;
		}
	}
	if (match_pg_tag == 0) {

		return 0;
	}
	for (i = 0; i < lu->maxmap; i++) {

		ig_tag = lu->map[i].ig_tag;
		igp = istgt_lu_find_initiatorgroup(istgt, ig_tag);
		if (igp == NULL) {
			ISTGT_ERRLOG("LU%d: ig_tag not found\n", lu->num);
			continue;
		}
		for (j = 0; j < igp->ninitiators; j++) {
			if (igp->initiators[j][0] == '!'
			    && (strcasecmp(&igp->initiators[j][1], "ALL") == 0
				|| strcasecmp(&igp->initiators[j][1], iqn) == 0)) {

				return 0;
			}
			if (strcasecmp(igp->initiators[j], "ALL") == 0
			    || strcasecmp(igp->initiators[j], iqn) == 0) {

				return 1;
			}
		}
	}


	return 0;
}
