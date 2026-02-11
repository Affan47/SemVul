CDB___memp_cmpr_coefficient(dbenv)
    DB_ENV *dbenv;
{
    u_int8_t ret = 0;

    if(!dbenv || !dbenv->mp_cmpr_info) {
	ret = default_cmpr_info.coefficient;
    } else {
	CDB___memp_cmpr_info_valid(dbenv, dbenv->mp_cmpr_info);
	ret = dbenv->mp_cmpr_info->coefficient;
    }

    return (ret);
}
