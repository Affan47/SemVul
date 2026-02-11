diva_bri_stop_adapter(diva_os_xdi_adapter_t *a)
{
	PISDN_ADAPTER IoAdapter = &a->xdi_adapter;
	int i = 100;

	if (!IoAdapter->port) {
		return (-1);
	}
	if (!IoAdapter->Initialized) {
		DBG_ERR(("A: A(%d) can't stop BRI adapter - not running",
			 IoAdapter->ANum))
			return (-1);
	}
	IoAdapter->Initialized = 0;


	diva_xdi_didd_remove_adapter(IoAdapter->ANum);


	a->clear_interrupts_proc = diva_bri_clear_interrupts;
	IoAdapter->a.ReadyInt = 1;
	IoAdapter->a.ram_inc(&IoAdapter->a, &PR_RAM->ReadyInt);
	do {
		diva_os_sleep(10);
	} while (i-- && a->clear_interrupts_proc);
	if (a->clear_interrupts_proc) {
		diva_bri_clear_interrupts(a);
		a->clear_interrupts_proc = NULL;
		DBG_ERR(("A: A(%d) no final interrupt from BRI adapter",
			 IoAdapter->ANum))
			}
	IoAdapter->a.ReadyInt = 0;


	IoAdapter->stop(IoAdapter);

	return (0);
}
