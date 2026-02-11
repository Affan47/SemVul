fn_locate_object_short_oid(void *state, git_buf *pathbuf) {
	loose_locate_object_state *sstate = (loose_locate_object_state *)state;

	if (git_buf_len(pathbuf) - sstate->dir_len != GIT_OID_HEXSZ - 2) {

		return 0;
	}

	if (git_path_isdir(pathbuf->ptr) == false) {


		if (!memcmp(sstate->short_oid + 2,
			(unsigned char *)pathbuf->ptr + sstate->dir_len,
			sstate->short_oid_len - 2)) {

			if (!sstate->found) {
				sstate->res_oid[0] = sstate->short_oid[0];
				sstate->res_oid[1] = sstate->short_oid[1];
				memcpy(sstate->res_oid+2, pathbuf->ptr+sstate->dir_len, GIT_OID_HEXSZ-2);
			}
			sstate->found++;
		}
	}

	if (sstate->found > 1)
		return git_odb__error_ambiguous("multiple matches in loose objects");

	return 0;
}
