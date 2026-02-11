interfacesChanged()
	{
		if(pub_addresses)
		{
			pub_addresses->setUseIPv6(global->haveMulticast6());
			pub_addresses->setUseIPv4(global->haveMulticast4());
		}
	}
