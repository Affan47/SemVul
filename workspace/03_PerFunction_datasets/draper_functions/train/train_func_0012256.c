clearSpecMods ()
{
	FTmodulatorI::clearSpecMods();

	LockMonitor pmlock(_specmodLock, __LINE__, __FILE__);
	_lastshifts.clear();
}
