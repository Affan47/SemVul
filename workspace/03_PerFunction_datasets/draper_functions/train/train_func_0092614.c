forceDirty()
{
	if(!isDirty())
	{
		_setForceDirty(true);


		signalListeners(PD_SIGNAL_DOCDIRTY_CHANGED);
	}
}
