r8712_wpspbc_event_callback(struct _adapter *adapter, u8 *pbuf)
{
	if (!adapter->securitypriv.wps_hw_pbc_pressed)
		adapter->securitypriv.wps_hw_pbc_pressed = true;
}
