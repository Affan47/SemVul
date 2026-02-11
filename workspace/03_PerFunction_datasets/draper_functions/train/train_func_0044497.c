find_database(const char *database, int for_write)
{
	char *whichdb;
	const char *ptr;
	struct mysql_conn *cur;

	if ((ptr = strchr(database, '/'))) {

		if (for_write) {
			whichdb = ast_strdupa(ptr + 1);
		} else {
			whichdb = ast_alloca(ptr - database + 1);
			strncpy(whichdb, database, ptr - database);
			whichdb[ptr - database] = '\0';
		}
	} else {
		whichdb = ast_strdupa(database);
	}

	AST_RWLIST_RDLOCK(&databases);
	AST_RWLIST_TRAVERSE(&databases, cur, list) {
		if (!strcmp(cur->unique_name, whichdb)) {
			ast_mutex_lock(&cur->lock);
			break;
		}
	}
	AST_RWLIST_UNLOCK(&databases);
	return cur;
}
