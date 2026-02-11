isSimilarTo(Change const & change) const
{
	if (type != change.type)
		return false;

	if (type == Change::UNCHANGED)
		return true;

	return author == change.author;
}
