entryTypes(int) const
	{
		QList<KeyStoreEntry::Type> list;
		list += KeyStoreEntry::TypeCertificate;
		list += KeyStoreEntry::TypeCRL;
		return list;
	}
