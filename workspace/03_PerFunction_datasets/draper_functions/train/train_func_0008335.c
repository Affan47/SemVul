vtos(const int* st, const int* en, std::string sep) {
	std::string s = "";
	if(st==en)
		return s;
	s = itos(*st);
	for(const int* it = st+1; it != en; it++)
		s += sep+itos(*it);
	return s;
}
