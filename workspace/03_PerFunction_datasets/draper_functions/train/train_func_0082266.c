is_custom_class(const char *name, int dotPos, const char *custom_var_classes)
{
	bool		result = false;
	const char *ccs = custom_var_classes;

	if (ccs != NULL)
	{
		const char *start = ccs;

		for (;; ++ccs)
		{
			char		c = *ccs;

			if (c == '\0' || c == ',')
			{
				if (dotPos == ccs - start && strncmp(start, name, dotPos) == 0)
				{
					result = true;
					break;
				}
				if (c == '\0')
					break;
				start = ccs + 1;
			}
		}
	}
	return result;
}
