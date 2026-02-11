dump(const list<string>& event)
{
	vector<uint16_t> data;
	list<string>::const_iterator i, begin = event.begin(), end = event.end();
	for( i=begin; i != end; ++i ) {
		data.clear();
		parse_hex(*i, data);
		cout << (i == begin? "Send" : "Receive") << endl;
		print_hex(data);
	}
	cout << endl;
}
