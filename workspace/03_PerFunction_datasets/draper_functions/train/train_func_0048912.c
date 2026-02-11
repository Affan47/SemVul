setAttributes(const gchar ** attributes)
{
	if (!attributes)
		return true;

	const gchar ** pp = attributes;
	while (*pp)
	{
		if (!setAttribute(pp[0],pp[1]))
			return false;
		pp += 2;
	}
	return true;
}
