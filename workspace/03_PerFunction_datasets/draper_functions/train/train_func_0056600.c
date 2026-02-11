db_sequence_create(seqp, dbp, flags)
	DB_SEQUENCE **seqp;
	DB *dbp;
	u_int32_t flags;
{
	DB_SEQUENCE *seq;
	ENV *env;
	int ret;

	env = dbp->env;

	DB_ILLEGAL_BEFORE_OPEN(dbp, "db_sequence_create");


	switch (flags) {
	case 0:
		break;
	default:
		return (__db_ferr(env, "db_sequence_create", 0));
	}

	if (dbp->type == DB_HEAP) {
		__db_errx(env, DB_STR("4016",
		    "Heap databases may not be used with sequences."));
		return (EINVAL);

	}


	if ((ret = __os_calloc(env, 1, sizeof(*seq), &seq)) != 0)
		return (ret);

	seq->seq_dbp = dbp;
	seq->close = __seq_close_pp;
	seq->get = __seq_get_pp;
	seq->get_cachesize = __seq_get_cachesize;
	seq->set_cachesize = __seq_set_cachesize;
	seq->get_db = __seq_get_db;
	seq->get_flags = __seq_get_flags;
	seq->get_key = __seq_get_key;
	seq->get_range = __seq_get_range;
	seq->initial_value = __seq_initial_value;
	seq->open = __seq_open_pp;
	seq->remove = __seq_remove;
	seq->set_flags = __seq_set_flags;
	seq->set_range = __seq_set_range;
	seq->stat = __seq_stat;
	seq->stat_print = __seq_stat_print;
	seq->seq_rp = &seq->seq_record;
	*seqp = seq;

	return (0);
}
