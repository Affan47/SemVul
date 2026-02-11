Function(const vector<string>& args){
	if(!AssertArgument(args, 4)) return ("");

	wstring target=ctow(args[1]);
	wstring pattern=ctow(args[2]);
	wstring subst=ctow(args[3]);
	int pos=_match(target, pattern,
				   ((args.size()>4) ? atoi(args[4].c_str()):-1), false);
	if(pos<0) return (args[1]);
	return wtoc(target.replace(pos, pattern.length(), subst));
}
