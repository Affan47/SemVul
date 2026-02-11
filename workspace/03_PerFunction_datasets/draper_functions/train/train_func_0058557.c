SwLedOff(struct adapter *padapter, struct LED_871x *pLed)
{
	u8	LedCfg;
	struct hal_data_8188e	*pHalData = GET_HAL_DATA(padapter);

	if (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		goto exit;

	LedCfg = usb_read8(padapter, REG_LEDCFG2);

	if (pHalData->bLedOpenDrain) {

		LedCfg &= 0x90;
		usb_write8(padapter, REG_LEDCFG2, (LedCfg | BIT(3)));
		LedCfg = usb_read8(padapter, REG_MAC_PINMUX_CFG);
		LedCfg &= 0xFE;
		usb_write8(padapter, REG_MAC_PINMUX_CFG, LedCfg);
	} else {
		usb_write8(padapter, REG_LEDCFG2, (LedCfg | BIT(3) | BIT(5) | BIT(6)));
	}
exit:
	pLed->bLedOn = false;
}
