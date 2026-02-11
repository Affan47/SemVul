parse_cookies(Request& r, Table *cookies){
	Table& result=*new Table(new Cookies_table_template_columns);

	for(Array_iterator<Table::element_type> i(*cookies); i.has_next(); )
		if(ArrayString* row=parse_cookie(r, *i.next()->get(0)))
			result+=row;

	return &result;
}
