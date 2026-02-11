rtl8723au_set_hw_type(struct rtw_adapter *padapter)
{
	padapter->chip_type = RTL8723A;
	padapter->HardwareType = HARDWARE_TYPE_RTL8723AU;
	DBG_8723A("CHIP TYPE: RTL8723A\n");
}
