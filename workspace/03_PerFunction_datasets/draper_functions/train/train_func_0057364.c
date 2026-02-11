stonith_walk_ghash(gpointer key, gpointer value, gpointer user_data)
{
	StonithNVpair*	u = user_data;

	if (NVcur <= NVmax && !NVerr) {
		u[NVcur].s_name = STRDUP(key);
		u[NVcur].s_value = STRDUP(value);
		if (u[NVcur].s_name == NULL || u[NVcur].s_value == NULL) {

			NVerr = TRUE;
			return;
		}
		++NVcur;
	}else{
		NVerr = TRUE;
	}
}
