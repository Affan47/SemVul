add_token(const token_type ttype, const string data, const bool force)
{
	if(settings["preserve_css"] || force) {
		token temp;
		temp.type = ttype;
		temp.data = (ttype == COMMENT) ? data : trim(data);
		csstokens.push_back(temp);
	}
}
