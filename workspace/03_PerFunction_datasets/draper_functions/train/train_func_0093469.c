entryList(int trackerId)
	{
		QList<KeyStoreEntry> out;
		int at = findItem(trackerId);
		if(at == -1)
			return out;
		Item &i = items[at];
		QList<KeyStoreEntryContext*> list = i.owner->entryList(i.storeContextId);
		for(int n = 0; n < list.count(); ++n)
		{
			KeyStoreEntry entry;
			entry.change(list[n]);
			out.append(entry);
		}
		return out;
	}
