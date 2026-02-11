result_get( value o, value n ) {
	result *r;
	const char *s;
	val_check_kind(o,k_result);
	val_check(n,int);
	r = RESULT(o);
	if( val_int(n) < 0 || val_int(n) >= r->nfields )
		neko_error();
	if( !r->current ) {
		result_next(o);
		if( !r->current )
			neko_error();
	}
	s = r->current[val_int(n)];
	return alloc_string( s?s:"" );
}
