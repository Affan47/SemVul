set_cookie( value name, value v ) {
	mcontext *c = CONTEXT();
	buffer b;
	value str;
	val_check(name,string);
	val_check(v,string);
	HEADERS_NOT_SENT("Cookie");
	b = alloc_buffer(NULL);
	val_buffer(b,name);
	buffer_append(b,"=");
	val_buffer(b,v);
	buffer_append(b,";");
	str = buffer_to_string(b);
	ap_table_add(c->r->headers_out,"Set-Cookie",val_string(str));
	return val_true;
}
