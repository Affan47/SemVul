haveSystemStore()
{

	KeyStoreManager::start("default");
	KeyStoreManager ksm;
	ksm.waitForBusyFinished();

	QStringList list = ksm.keyStores();
	for(int n = 0; n < list.count(); ++n)
	{
		KeyStore ks(list[n], &ksm);
		if(ks.type() == KeyStore::System && ks.holdsTrustedCertificates())
			return true;
	}
	return false;
}
