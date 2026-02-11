copyFaustSources(const char* projname, const vector<string>& pathnames)
{
	string srcdir = subst("$0/src", projname);

	makedir(srcdir.c_str());

	for (unsigned int i=0; i< pathnames.size(); i++) {
		ifstream src;
		ofstream dst;
		string faustfile = pathnames[i];
		string copy = subst("$0/$1", srcdir, filebasename(faustfile.c_str()));


		src.open(faustfile.c_str(), ifstream::in);
		dst.open(copy.c_str(), ofstream::out);
		string	s;
		while ( getline(src,s) ) dst << s << endl;
	}
}
