sameContent(const NetInterfaceProvider::Info &a, const NetInterfaceProvider::Info &b)
	{

		if(a.name == b.name && a.isLoopback == b.isLoopback && a.addresses == b.addresses && a.gateway == b.gateway)
			return true;
		return false;
	}
