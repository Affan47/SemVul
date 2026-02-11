ReadLdif(std::istream &is, Barry::Contact &con)
{
	std::string line;


	con.Clear();
	ClearHeuristics();


	bool found = false;
	while( std::getline(is, line) ) {
		if( strncmp(line.c_str(), "dn: ", 4) == 0 ) {
			found = true;
			break;
		}
	}
	if( !found )
		return false;


	std::string coded, decode, attr, data;
	bool b64field = false;


	while( getline(is, line) && line.size() ) {

		if( b64field ) {

			if( line[0] == ' ' ) {
				coded += "\n";
				coded += line;
				continue;
			}
			else {


				base64_decode(coded, decode);
				DoWrite(con, attr, decode);
				coded.clear();
				b64field = false;
			}

		}


		std::string::size_type delim = line.find(':'), dstart;
		if( delim == std::string::npos )
			continue;

		attr.assign(line, 0, delim);
		dstart = delim + 1;
		while( line[dstart] == ' ' || line[dstart] == ':' )
			dstart++;
		data = line.substr(dstart);


		if( line[delim + 1] == ':' ) {
			coded = data;
			b64field = true;
			continue;
		}

		DoWrite(con, attr, data);
	}

	if( b64field ) {

		base64_decode(coded, decode);
		DoWrite(con, attr, decode);
		coded.clear();
		b64field = false;
	}

	return RunHeuristics(con);
}
