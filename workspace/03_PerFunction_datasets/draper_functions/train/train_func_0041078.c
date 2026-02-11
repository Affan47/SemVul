Function(const vector<string>& args)
{
	if(!AssertArgument(args, 2, 2)) return ("");

	return PathToBaseDir(CanonicalPath(args[1]));
}
