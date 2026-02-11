CheckSize(const Data &data, unsigned int required)
{
	const unsigned char *pd = data.GetData();

	if( GetSize(pd) != (unsigned int) data.GetSize() ||
	    data.GetSize() < required ||
	    pd[4] != SB_COMMAND_FETCHED_ATTRIBUTE )
	{
		dout(_("Probe: Parse data failure: ")
			<< "GetSize(pd): " << GetSize(pd)
			<< ", data.GetSize(): " << data.GetSize()
			<< ", pd[4]: " << (unsigned int) pd[4]);
		return false;
	}

	return true;
}
