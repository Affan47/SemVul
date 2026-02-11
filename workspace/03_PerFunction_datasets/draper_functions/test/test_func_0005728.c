connect_didd(void)
{
	int x = 0;
	int dadapter = 0;
	IDI_SYNC_REQ req;
	DESCRIPTOR DIDD_Table[MAX_DESCRIPTORS];

	DIVA_DIDD_Read(DIDD_Table, sizeof(DIDD_Table));

	for (x = 0; x < MAX_DESCRIPTORS; x++) {
		if (DIDD_Table[x].type == IDI_DADAPTER) {
			dadapter = 1;
			memcpy(&DAdapter, &DIDD_Table[x], sizeof(DAdapter));
			req.didd_notify.e.Req = 0;
			req.didd_notify.e.Rc =
				IDI_SYNC_REQ_DIDD_REGISTER_ADAPTER_NOTIFY;
			req.didd_notify.info.callback = (void *)didd_callback;
			req.didd_notify.info.context = NULL;
			DAdapter.request((ENTITY *)&req);
			if (req.didd_notify.e.Rc != 0xff) {
				stop_dbg();
				return (0);
			}
			notify_handle = req.didd_notify.info.handle;
		} else if (DIDD_Table[x].type == IDI_DIMAINT) {
			memcpy(&MAdapter, &DIDD_Table[x], sizeof(DAdapter));
			dprintf = (DIVA_DI_PRINTF) MAdapter.request;
			start_dbg();
		}
	}

	if (!dadapter) {
		stop_dbg();
	}

	return (dadapter);
}
