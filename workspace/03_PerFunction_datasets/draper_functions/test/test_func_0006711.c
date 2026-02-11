where() const
{
	std::stringstream result;
	result << "in file '" << _path << "', line " << _line;
	const PageReader* pParent = _pParent;
	while (pParent)
	{
		result << "\n\tincluded from file '"<<  pParent->_path << "', line " << pParent->_line;
		pParent = pParent->_pParent;
	}
	return result.str();
}
