BlinkHandler(struct LED_871x *pLed)
{
	struct adapter *padapter = pLed->padapter;

	if ((padapter->bSurpriseRemoved) || (padapter->bDriverStopped))
		return;

	SwLedBlink1(pLed);
}
