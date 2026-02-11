writeEnvirEnd(bool useSetSpace) const
{
	string const name = envName(space, useSetSpace);
	return name.empty() ? string() : "\\end{" + name + '}';
}
