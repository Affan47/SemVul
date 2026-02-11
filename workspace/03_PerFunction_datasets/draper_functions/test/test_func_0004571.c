setTimeout()
{
	if (handlerTimeoutVal == 0 && myimap)
		handlerTimeoutVal=myimap->timeoutSetting;

	time(&timeoutAt);
	timeoutAt += handlerTimeoutVal;
}
