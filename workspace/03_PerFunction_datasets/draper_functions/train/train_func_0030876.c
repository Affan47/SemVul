providerForIOType(PKey::Type type, const PKeyContext *prefer = 0)
{
	Provider *preferProvider = 0;
	if(prefer)
	{
		preferProvider = prefer->provider();
		if(prefer && prefer->supportedIOTypes().contains(type))
			return preferProvider;
	}

	ProviderList pl = allProviders();
	for(int n = 0; n < pl.count(); ++n)
	{
		if(preferProvider && pl[n] == preferProvider)
			continue;

		if(Getter_IOType::getList(pl[n]).contains(type))
			return pl[n];
	}
	return 0;
}
