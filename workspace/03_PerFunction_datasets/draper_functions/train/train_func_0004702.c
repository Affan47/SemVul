_setup_association_cond_qos(slurmdb_association_cond_t *assoc_cond,
					 char *cluster_name)
{
	int set = 0;
	ListIterator itr = NULL;
	char *object = NULL;
	char *prefix = "t1";
	char *extra = NULL;

	if (!assoc_cond)
		return NULL;


	if (assoc_cond->qos_list && list_count(assoc_cond->qos_list)) {


		assoc_cond->with_sub_accts = 1;
		prefix = "t2";
		xstrfmtcat(extra, ", \"%s_%s\" as t2 where "
			   "(t1.lft between t2.lft and t2.rgt) && (",
			   cluster_name, assoc_table);
		set = 0;
		itr = list_iterator_create(assoc_cond->qos_list);
		while ((object = list_next(itr))) {
			if (set)
				xstrcat(extra, " || ");
			xstrfmtcat(extra,
				   "(%s.qos like '%%,%s' "
				   "|| %s.qos like '%%,%s,%%' "
				   "|| %s.delta_qos like '%%,+%s' "
				   "|| %s.delta_qos like '%%,+%s,%%')",
				   prefix, object, prefix, object,
				   prefix, object, prefix, object);
			set = 1;
		}
		list_iterator_destroy(itr);
		xstrcat(extra, ") &&");
	} else if (assoc_cond->with_sub_accts) {
		prefix = "t2";
		xstrfmtcat(extra, ", \"%s_%s\" as t2 where "
			   "(t1.lft between t2.lft and t2.rgt) &&",
			   cluster_name, assoc_table);
	} else
		xstrcat(extra, " where");
	return extra;
}
