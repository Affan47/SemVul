printStringMapContent(map<string,string>& m, const string& name) {
	bool trace = false;
	if(trace) {
		cout << name << ".size() = " << m.size() << endl;
		map<string,string>::iterator it;
		int i = 1;
		for(it = m.begin(); it!=m.end(); ++it)
			cout << i++ << ".\t" << name << "[" << it->first << "] \t= '" << it->second << "'" << endl;
	}
}
