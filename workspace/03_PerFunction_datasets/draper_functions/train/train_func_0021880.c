get_element()
{
	if (!impl)
	{
		static CL_DomElement null;
		return null;
	}
	return impl->element;
}
