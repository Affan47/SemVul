Function(const vector<string>& args)
{
	if(!AssertArgument(args, 3, 3)) return ("");

	string dirname=CanonicalPath(Engine->GetDataPath(), args[2]);

	DIR *dirhandle;
	struct dirent *direntry;
	if((dirhandle=opendir(dirname.c_str()))==NULL) return("");

	Engine->ClearEntry(args[1]);

	while((direntry=readdir(dirhandle))!=NULL) {
		string entry=direntry->d_name;
		if((entry!=".")&&(entry!="..")) Engine->CreateEntry(args[1]).Push(Engine->CreateStrWord(entry));
	}

	closedir(dirhandle);

	return("");
}
