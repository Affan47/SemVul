width(char_type c) const
{
	if (smallcaps_shape_)
		return smallcapsWidth(c);

	int value = width_cache_.value(c, outOfLimitMetric);
	if (value != outOfLimitMetric)
		return value;

	if (is_utf16(c))
		value = metrics_.width(ucs4_to_qchar(c));
	else
		value = metrics_.width(toqstr(docstring(1, c)));

	width_cache_.insert(c, value);

	return value;
}
