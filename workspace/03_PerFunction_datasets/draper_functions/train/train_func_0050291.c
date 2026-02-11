connect( value params  ) {
	value host, port, user, pass, socket;
	val_check(params,object);
	host = val_field(params,val_id("host"));
	port = val_field(params,val_id("port"));
	user = val_field(params,val_id("user"));
	pass = val_field(params,val_id("pass"));
	socket = val_field(params,val_id("socket"));
	val_check(host,string);
	val_check(port,int);
	val_check(user,string);
	val_check(pass,string);
	if( !val_is_string(socket) && !val_is_null(socket) )
		neko_error();
	{
		connection *c = (connection*)alloc(sizeof(connection));
		value v;
		c->m = mysql_init(NULL);
		c->conv_string = NULL;
		c->conv_date = NULL;
		c->conv_bytes = NULL;
		if( mysql_real_connect(c->m,val_string(host),val_string(user),val_string(pass),NULL,val_int(port),val_is_null(socket)?NULL:val_string(socket),0) == NULL ) {
			buffer b = alloc_buffer("Failed to connect to mysql server : ");
			buffer_append(b,mysql_error(c->m));
			mysql_close(c->m);
			bfailure(b);
		}
		v = alloc_abstract(k_connection,c);
		val_gc(v,free_connection);
		return v;
	}
}
