haveAlready(const QString &name) const
{
	if(def && name == def->name())
		return true;

	for(int n = 0; n < providerItemList.count(); ++n)
	{
		ProviderItem *pi = providerItemList[n];
		if(pi->p && pi->p->name() == name)
			return true;
	}

	return false;
}
