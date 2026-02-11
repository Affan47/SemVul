get_address() const
{
	if (impl) return impl->address;
	return CL_IPAddress(0);
}
