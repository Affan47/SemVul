GetFixedNestedVaryingSemantic(const std::string& parentStructSemantic, int ii)
{
	int baseIdx = 0;
	std::stringstream var;
	const size_t i = parentStructSemantic.find_first_of("0123456789");
	if (i != std::string::npos)
	{
		std::stringstream(&parentStructSemantic[i]) >> baseIdx;
		var << parentStructSemantic.substr(0, i);
	}
	else
		var << parentStructSemantic;

	var << (baseIdx + ii);

	return var.str();
}
