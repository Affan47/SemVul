request( value v, value sql ) {
	database *db;
	result *r;
	const char *tl;
	int i,j;
	val_check_kind(v,k_db);
	val_check(sql,string);
	db = val_db(v);
	r = (result*)alloc(sizeof(result));
	r->db = db;
	if( sqlite3_prepare(db->db,val_string(sql),val_strlen(sql),&r->r,&tl) != SQLITE_OK ) {
		buffer b = alloc_buffer("Sqlite error in ");
		val_buffer(b,sql);
		buffer_append(b," : ");
		buffer_append(b,sqlite3_errmsg(db->db));
		val_throw(buffer_to_string(b));
	}
	if( *tl ) {
		sqlite3_finalize(r->r);
		val_throw(alloc_string("Cannot execute several SQL requests at the same time"));
	}
	r->ncols = sqlite3_column_count(r->r);
	r->names = (field*)alloc_private(sizeof(field)*r->ncols);
	r->bools = (int*)alloc_private(sizeof(int)*r->ncols);
	r->first = 1;
	r->done = 0;
	for(i=0;i<r->ncols;i++) {
		field id = val_id(sqlite3_column_name(r->r,i));
		const char *dtype = sqlite3_column_decltype(r->r,i);
		for(j=0;j<i;j++)
			if( r->names[j] == id ) {
				if( strcmp(sqlite3_column_name(r->r,i),sqlite3_column_name(r->r,j)) == 0 ) {
					buffer b = alloc_buffer("Error, same field is two times in the request ");
					val_buffer(b,sql);
					sqlite3_finalize(r->r);
					val_throw(buffer_to_string(b));
				} else {
					buffer b = alloc_buffer("Error, same field ids for : ");
					buffer_append(b,sqlite3_column_name(r->r,i));
					buffer_append(b," and ");
					buffer_append(b,sqlite3_column_name(r->r,j));
					buffer_append_char(b,'.');
					sqlite3_finalize(r->r);
					val_throw(buffer_to_string(b));
				}
			}
		r->names[i] = id;
		r->bools[i] = dtype?(strcmp(dtype,"BOOL") == 0):0;
	}

	if( db->last != NULL )
		finalize_result(val_result(db->last),0);
	db->last = alloc_abstract(k_result,r);
	return db->last;
}
