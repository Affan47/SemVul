_setup_wckey_cond_limits(slurmdb_wckey_cond_t *wckey_cond,
				    char **extra)
{
	int set = 0;
	ListIterator itr = NULL;
	char *object = NULL;
	char *prefix = "t1";
	if (!wckey_cond)
		return 0;

	if (wckey_cond->with_deleted)
		xstrfmtcat(*extra, " where (%s.deleted=0 || %s.deleted=1)",
			   prefix, prefix);
	else
		xstrfmtcat(*extra, " where %s.deleted=0", prefix);

	if (wckey_cond->only_defs) {
		set = 1;
		xstrfmtcat(*extra, " && (%s.is_def=1)", prefix);
	}

	if (wckey_cond->name_list && list_count(wckey_cond->name_list)) {
		set = 0;
		xstrcat(*extra, " && (");
		itr = list_iterator_create(wckey_cond->name_list);
		while ((object = list_next(itr))) {
			if (set)
				xstrcat(*extra, " || ");
			xstrfmtcat(*extra, "%s.wckey_name='%s'",
				   prefix, object);
			set = 1;
		}
		list_iterator_destroy(itr);
		xstrcat(*extra, ")");
	}

	if (wckey_cond->id_list && list_count(wckey_cond->id_list)) {
		set = 0;
		xstrcat(*extra, " && (");
		itr = list_iterator_create(wckey_cond->id_list);
		while ((object = list_next(itr))) {
			if (set)
				xstrcat(*extra, " || ");
			xstrfmtcat(*extra, "%s.id_wckey=%s", prefix, object);
			set = 1;
		}
		list_iterator_destroy(itr);
		xstrcat(*extra, ")");
	}

	if (wckey_cond->user_list && list_count(wckey_cond->user_list)) {
		set = 0;
		xstrcat(*extra, " && (");
		itr = list_iterator_create(wckey_cond->user_list);
		while ((object = list_next(itr))) {
			if (set)
				xstrcat(*extra, " || ");
			xstrfmtcat(*extra, "%s.user='%s'", prefix, object);
			set = 1;
		}
		list_iterator_destroy(itr);
		xstrcat(*extra, ")");
	}

	return set;
}
