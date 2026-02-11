toDER(const SecureArray &passphrase, PBEAlgorithm pbe) const
{
	SecureArray out;
	if(pbe == PBEDefault)
		pbe = get_pbe_default();
	const PKeyContext *cur = static_cast<const PKeyContext *>(context());
	Provider *p = providerForPBE(pbe, type(), cur);
	if(!p)
		return out;
	if(cur->provider() == p)
	{
		out = cur->privateToDER(passphrase, pbe);
	}
	else
	{
		PKeyContext *pk = static_cast<PKeyContext *>(getContext("pkey", p));
		if(pk->importKey(cur->key()))
			out = pk->privateToDER(passphrase, pbe);
		delete pk;
	}
	return out;
}
