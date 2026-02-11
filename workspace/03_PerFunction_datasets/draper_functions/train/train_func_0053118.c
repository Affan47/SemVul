skip_space (istream& in) {
    char ch;
    while(isspace(ch=in.get()) && in.good());
    if (in.good())
	in.putback(ch);
    return (in.good()||in.eof()) ? 0 : -1;
}
