compare_same_type(const basic & other) const
{
	GINAC_ASSERT(is_a<wildcard>(other));
	const wildcard &o = static_cast<const wildcard &>(other);

	if (label == o.label)
		return 0;
	else
		return label < o.label ? -1 : 1;
}
