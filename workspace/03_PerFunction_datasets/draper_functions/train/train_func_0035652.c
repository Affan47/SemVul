usb_AggSettingTxUpdate(struct adapter *Adapter)
{
	struct hal_data_8188e	*haldata = GET_HAL_DATA(Adapter);
	u32 value32;

	if (Adapter->registrypriv.wifi_spec)
		haldata->UsbTxAggMode = false;

	if (haldata->UsbTxAggMode) {
		value32 = usb_read32(Adapter, REG_TDECTRL);
		value32 = value32 & ~(BLK_DESC_NUM_MASK << BLK_DESC_NUM_SHIFT);
		value32 |= ((haldata->UsbTxAggDescNum & BLK_DESC_NUM_MASK) << BLK_DESC_NUM_SHIFT);

		usb_write32(Adapter, REG_TDECTRL, value32);
	}
}
