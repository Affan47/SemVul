split(ArrayString& result,
		   size_t& pos_after,
		   const String& delim, Language lang,
		   int limit) const {
	if(is_empty())
		return;
	if(!delim.is_empty()) {
		size_t pos_before;

		for(; (pos_before=pos(delim, pos_after, lang))!=STRING_NOT_FOUND && limit; limit--) {
			result+=&mid(pos_after, pos_before);
			pos_after=pos_before+delim.length();
		}

		if(pos_after<length() && limit) {
			result+=&mid(pos_after, length());
			pos_after=length();
		}
	} else {
		result+=this;
		pos_after+=length();
	}
}
