rsdb_exec_fetch(struct rsdb_table *table, const char *format, ...)
{
	static char buf[BUFSIZE * 4];
	va_list args;
	char *errmsg;
	char **data;
	int pos;
	unsigned int retval;
	int i, j;

	va_start(args, format);
	retval = rs_vsnprintf(buf, sizeof(buf), format, args);
	va_end(args);

	if(retval >= sizeof(buf))
	{
		mlog("fatal error: length problem with compiling sql");
	}

	if((retval =
	    sqlite3_get_table(rb_bandb, buf, &data, &table->row_count, &table->col_count, &errmsg)))
	{
		int success = 0;

		switch (retval)
		{
		case SQLITE_BUSY:
			for(i = 0; i < 5; i++)
			{
				rb_sleep(0, 500000);
				if(!sqlite3_get_table
				   (rb_bandb, buf, &data, &table->row_count, &table->col_count,
				    &errmsg))
				{
					success++;
					break;
				}
			}

			if(success)
				break;

			mlog("fatal error: problem with db file: %s", errmsg);
			break;

		default:
			mlog("fatal error: problem with db file: %s", errmsg);
			break;
		}
	}


	table->arg = data;

	if(table->row_count == 0)
	{
		table->row = NULL;
		return;
	}


	pos = table->col_count;
	table->row = rb_malloc(sizeof(char **) * table->row_count);
	for(i = 0; i < table->row_count; i++)
	{
		table->row[i] = rb_malloc(sizeof(char *) * table->col_count);

		for(j = 0; j < table->col_count; j++)
		{
			table->row[i][j] = data[pos++];
		}
	}
}
