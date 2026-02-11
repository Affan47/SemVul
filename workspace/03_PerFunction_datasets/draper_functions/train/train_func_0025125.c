hciops_set_pairable(int index, gboolean pairable)
{
	struct btd_adapter *adapter;

	DBG("hci%d pairable %d", index, pairable);

	adapter = manager_find_adapter(&devs[index].bdaddr);
	if (adapter)
		btd_adapter_pairable_changed(adapter, pairable);

	devs[index].pairable = pairable;

	return 0;
}
