unloadModule (XAP_Module * pModule)
{
	UT_ASSERT (pModule);
	if (pModule == 0) return;

	UT_ASSERT (pModule->getCreator () == this);
	if (pModule->getCreator () != this) return;

	UT_sint32 ndx = m_modules->findItem (pModule);
	if (ndx == -1)
	{
		UT_ASSERT (UT_SHOULD_NOT_HAPPEN);
		UT_DEBUGMSG (("Could not unload module\n"));
		return;
	}
	unloadModule (ndx);
}
