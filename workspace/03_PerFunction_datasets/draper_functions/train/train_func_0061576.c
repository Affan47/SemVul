request( value o, value r )  {
	MYSQL_RES *res;
	connection *c;
	val_check_kind(o,k_connection);
	val_check(r,string);
	c = CNX(o);
	if( mysql_real_query(c->m,val_string(r),val_strlen(r)) != 0 )
		error(c->m,val_string(r));
	res = mysql_store_result(c->m);
	if( res == NULL ) {
		if( mysql_field_count(c->m) == 0 )
			return alloc_int( (int)mysql_affected_rows(c->m) );
		else
			error(c->m,val_string(r));
	}
	return alloc_result(c,res);
}
