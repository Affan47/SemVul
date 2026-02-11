load_options()
{
	char *opt;
	char *s;

    if (!optset && (s=getenv("MDBOPTS"))) {
		opt = strtok(s, ":");
		while (opt) {
        	if (!strcmp(opt, "use_index")) opts |= MDB_USE_INDEX;
        	if (!strcmp(opt, "no_memo")) opts |= MDB_NO_MEMO;
        	if (!strcmp(opt, "debug_like")) opts |= MDB_DEBUG_LIKE;
        	if (!strcmp(opt, "debug_write")) opts |= MDB_DEBUG_WRITE;
        	if (!strcmp(opt, "debug_usage")) opts |= MDB_DEBUG_USAGE;
        	if (!strcmp(opt, "debug_ole")) opts |= MDB_DEBUG_OLE;
        	if (!strcmp(opt, "debug_row")) opts |= MDB_DEBUG_ROW;
        	if (!strcmp(opt, "debug_props")) opts |= MDB_DEBUG_PROPS;
        	if (!strcmp(opt, "debug_all")) {
				opts |= MDB_DEBUG_LIKE;
				opts |= MDB_DEBUG_WRITE;
				opts |= MDB_DEBUG_USAGE;
				opts |= MDB_DEBUG_OLE;
				opts |= MDB_DEBUG_ROW;
				opts |= MDB_DEBUG_PROPS;
			}
			opt = strtok(NULL,":");
		}
    }
	optset = 1;
}
