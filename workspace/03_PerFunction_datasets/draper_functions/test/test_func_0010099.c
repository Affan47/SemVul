item(size_t column) {
	if(valid(fcurrent)) {
		element_type row=get(fcurrent);
		if(column<row->count())
			return row->get(column);
	}
	return 0;
}
