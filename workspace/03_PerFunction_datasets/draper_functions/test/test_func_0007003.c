hostName() const
{
	try
	{
		return DNS::resolve(_address.host().toString()).name();
	}
	catch (HostNotFoundException&)
	{
	}
	catch (NoAddressFoundException&)
	{
	}
	catch (DNSException&)
	{
	}
	catch (IOException&)
	{
	}
	return _address.host().toString();
}
