__db_stat_arg(dbp, flags)
	DB *dbp;
	u_int32_t flags;
{
	ENV *env;

	env = dbp->env;


	LF_CLR(DB_READ_COMMITTED | DB_READ_UNCOMMITTED);
	switch (flags) {
	case 0:
	case DB_FAST_STAT:
		break;
	default:
		return (__db_ferr(env, "DB->stat", 0));
	}

	return (0);
}
