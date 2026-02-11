concat_node_state_cond_list(List cond_list, char *prefix,
			    char *col, char **cond_str)
{
	int set = 0;
	char *object;
	ListIterator itr = NULL;

	if(cond_list && list_count(cond_list)) {
		xstrcat(*cond_str, " AND (");
		itr = list_iterator_create(cond_list);
		while((object = list_next(itr))) {
			if(set)
				xstrcat(*cond_str, " OR ");


			if (prefix)
				xstrfmtcat(*cond_str, "(%s.%s&%s)=%s",
					   prefix, col, object, object);
			else
				xstrfmtcat(*cond_str, "(%s&%s)=%s",
					   col, object, object);
			set = 1;
		}
		list_iterator_destroy(itr);
		xstrcat(*cond_str, ")");
	}
}
