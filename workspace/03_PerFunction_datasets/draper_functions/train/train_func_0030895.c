set_retry_cnt_mods(Slapi_PBlock *pb, Slapi_Mods *smods, int count)
{
	char 		*timestr;
	time_t		unlock_time;
	char        retry_cnt[8];
	const char *dn = NULL;
	Slapi_DN *sdn = NULL;
	passwdPolicy *pwpolicy = NULL;
	int rc = 0;

	slapi_pblock_get( pb, SLAPI_TARGET_SDN, &sdn );
	dn = slapi_sdn_get_dn(sdn);
	pwpolicy = new_passwdPolicy(pb, dn);

	if (smods) {
		sprintf ( retry_cnt, "%d", count );
		slapi_mods_add_string(smods, LDAP_MOD_REPLACE, "passwordRetryCount", retry_cnt);

		if ( count >=  pwpolicy->pw_maxfailure ) {


			if ( pwpolicy->pw_unlock == 0 ) {

				unlock_time = NO_TIME;
			} else {
				unlock_time = time_plus_sec ( current_time(),
											  pwpolicy->pw_lockduration );
			}
			timestr= format_genTime ( unlock_time );
			slapi_mods_add_string(smods, LDAP_MOD_REPLACE, "accountUnlockTime", timestr);
			slapi_ch_free((void **)&timestr);
			rc = LDAP_CONSTRAINT_VIOLATION;
		}
	}
	return rc;
}
