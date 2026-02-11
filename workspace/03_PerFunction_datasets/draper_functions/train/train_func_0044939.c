GetParam(const char *name, int nth)
{
	std::string ret;

	if( !m_attr )
		return ret;

	b_VFormatParam *param = b_vformat_attribute_find_param(m_attr, name, 0);
	if( !param )
		return ret;

	const char *value = b_vformat_attribute_param_get_nth_value(param, nth);
	if( value )
		ret = value;

	return ret;
}
