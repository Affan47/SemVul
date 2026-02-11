is_equal_same_type(const basic & other) const
{
	GINAC_ASSERT(is_a<fderivative>(other));
	const fderivative & o = static_cast<const fderivative &>(other);

	if (parameter_set != o.parameter_set)
		return false;
	else
		return inherited::is_equal_same_type(o);
}
