findNextNonDeletedIndex(unsigned int index) const
{
	std::size_t next = index + 1;
	const std::size_t len = inputLine.size();
	while (next < len && isDeleted[next] == DELETE)
		next++;
	return static_cast<unsigned int>(next);
}
