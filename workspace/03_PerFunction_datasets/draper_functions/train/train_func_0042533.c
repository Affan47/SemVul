ensureAccess()
{
	if(!ensureAvailable())
	{
		d->accessible = false;
		return false;
	}
	bool ok = static_cast<KeyStoreEntryContext *>(context())->ensureAccess();
	d->accessible = ok;
	return d->accessible;
}
