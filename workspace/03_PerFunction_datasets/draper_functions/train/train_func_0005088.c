Function(const vector<string>& args)
{
	if(!AssertArgument(args, 2, 2)) return ("");
	Engine->EraseSAORIModule(args[1]);
	return ("");
}
