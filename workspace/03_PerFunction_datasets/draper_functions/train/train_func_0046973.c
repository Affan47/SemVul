find(const QString &name) const
{
	ProviderItem *i = 0;
	Provider *p = 0;

	providerMutex.lock();
	if(def && name == def->name())
	{
		p = def;
	}
	else
	{
		for(int n = 0; n < providerItemList.count(); ++n)
		{
			ProviderItem *pi = providerItemList[n];
			if(pi->p && pi->p->name() == name)
			{
				i = pi;
				p = pi->p;
				break;
			}
		}
	}
	providerMutex.unlock();

	if(i)
		i->ensureInit();
	return p;
}
