EmitIfNotEmpty (std::stringstream& out, const std::stringstream& str)
{
	if (str.str().size())
		out << str.str() << "\n";
}
