select_pg_timeout(struct multipath *mp)
{
	if (mp->mpe && mp->mpe->pg_timeout != PGTIMEOUT_UNDEF) {
		mp->pg_timeout = mp->mpe->pg_timeout;
		if (mp->pg_timeout > 0)
			condlog(3, "%s: pg_timeout = %d (multipath setting)",
				mp->alias, mp->pg_timeout);
		else
			condlog(3, "%s: pg_timeout = NONE (multipath setting)",
				mp->alias);
		return 0;
	}
	if (mp->hwe && mp->hwe->pg_timeout != PGTIMEOUT_UNDEF) {
		mp->pg_timeout = mp->hwe->pg_timeout;
		if (mp->pg_timeout > 0)
			condlog(3, "%s: pg_timeout = %d (controller setting)",
				mp->alias, mp->pg_timeout);
		else
			condlog(3, "%s: pg_timeout = NONE (controller setting)",
				mp->alias);
		return 0;
	}
	if (conf->pg_timeout != PGTIMEOUT_UNDEF) {
		mp->pg_timeout = conf->pg_timeout;
		if (mp->pg_timeout > 0)
			condlog(3, "%s: pg_timeout = %d (config file default)",
				mp->alias, mp->pg_timeout);
		else
			condlog(3,
				"%s: pg_timeout = NONE (config file default)",
				mp->alias);
		return 0;
	}
	mp->pg_timeout = PGTIMEOUT_UNDEF;
	condlog(3, "pg_timeout = NONE (internal default)");
	return 0;
}
