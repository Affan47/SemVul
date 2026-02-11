dump(std::ostream& ostr, const std::string& delimiter) const
{
	for (Stack::const_iterator it = _stack.begin(); it != _stack.end(); ++it)
	{
		ostr << it->info;
		if (it->file)
			ostr << " (in \"" << it->file << "\", line " << it->line << ")";
		ostr << delimiter;
	}
}
