escape( value o, value s ) {
	int len;
	value sout;
	val_check_kind(o,k_connection);
	val_check(s,string);
	len = val_strlen(s) * 2;
	sout = alloc_empty_string(len);
	len = mysql_real_escape_string(CNX(o)->m,val_string(sout),val_string(s),val_strlen(s));
	if( len < 0 ) {
		buffer b = alloc_buffer("Unsupported charset : ");
		buffer_append(b,mysql_character_set_name(CNX(o)->m));
		bfailure(b);
	}
	val_set_length(sout,len);
	return sout;
}
