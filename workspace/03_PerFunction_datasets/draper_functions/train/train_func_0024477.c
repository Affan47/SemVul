didd_callback(void *context, DESCRIPTOR *adapter,
			   int removal)
{
	if (adapter->type == IDI_DADAPTER) {
		DBG_ERR(("Notification about IDI_DADAPTER change ! Oops."));
		return (NULL);
	} else if (adapter->type == IDI_DIMAINT) {
		if (removal) {
			stop_dbg();
		} else {
			memcpy(&MAdapter, adapter, sizeof(MAdapter));
			dprintf = (DIVA_DI_PRINTF) MAdapter.request;
			DbgRegister("User IDI", DRIVERRELEASE_IDI, DBG_DEFAULT);
		}
	} else if ((adapter->type > 0) && (adapter->type < 16)) {
		if (removal) {
			um_remove_card(adapter);
		} else {
			um_new_card(adapter);
		}
	}
	return (NULL);
}
