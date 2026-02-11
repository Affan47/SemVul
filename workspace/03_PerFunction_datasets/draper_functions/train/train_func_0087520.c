get_types(QStringList (*get_func)(Provider *p), const QString &provider)
{
	QStringList out;
	if(!provider.isEmpty())
	{
		Provider *p = providerForName(provider);
		if(p)
			out = get_func(p);
	}
	else
	{
		ProviderList pl = allProviders();
		foreach(Provider *p, pl)
			mergeList(&out, get_func(p));
	}
	return out;
}
