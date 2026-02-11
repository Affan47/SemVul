CardDisableRTL8188EU(struct adapter *Adapter)
{
	u8 val8;
	struct hal_data_8188e	*haldata	= GET_HAL_DATA(Adapter);

	RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("CardDisableRTL8188EU\n"));


	val8 = usb_read8(Adapter, REG_TX_RPT_CTRL);
	usb_write8(Adapter, REG_TX_RPT_CTRL, val8&(~BIT(1)));


	usb_write8(Adapter, REG_CR, 0x0);


	rtl88eu_pwrseqcmdparsing(Adapter, PWR_CUT_ALL_MSK,
				 PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,
				 Rtl8188E_NIC_LPS_ENTER_FLOW);


	val8 = usb_read8(Adapter, REG_MCUFWDL);
	if ((val8 & RAM_DL_SEL) && Adapter->bFWReady) {

		val8 = usb_read8(Adapter, REG_SYS_FUNC_EN+1);
		val8 &= ~BIT(2);
		usb_write8(Adapter, REG_SYS_FUNC_EN+1, val8);
	}


	usb_write8(Adapter, REG_MCUFWDL, 0);


	val8 = usb_read8(Adapter, REG_32K_CTRL);
	usb_write8(Adapter, REG_32K_CTRL, val8&(~BIT(0)));


	rtl88eu_pwrseqcmdparsing(Adapter, PWR_CUT_ALL_MSK,
				 PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,
				 Rtl8188E_NIC_DISABLE_FLOW);


	val8 = usb_read8(Adapter, REG_RSV_CTRL+1);
	usb_write8(Adapter, REG_RSV_CTRL+1, (val8&(~BIT(3))));
	val8 = usb_read8(Adapter, REG_RSV_CTRL+1);
	usb_write8(Adapter, REG_RSV_CTRL+1, val8 | BIT(3));


	val8 = usb_read8(Adapter, GPIO_IN);
	usb_write8(Adapter, GPIO_OUT, val8);
	usb_write8(Adapter, GPIO_IO_SEL, 0xFF);

	val8 = usb_read8(Adapter, REG_GPIO_IO_SEL);
	usb_write8(Adapter, REG_GPIO_IO_SEL, (val8<<4));
	val8 = usb_read8(Adapter, REG_GPIO_IO_SEL+1);
	usb_write8(Adapter, REG_GPIO_IO_SEL+1, val8|0x0F);
	usb_write32(Adapter, REG_BB_PAD_CTRL, 0x00080808);
	haldata->bMacPwrCtrlOn = false;
	Adapter->bFWReady = false;
}
