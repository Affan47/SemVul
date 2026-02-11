diva_4bri_start_adapter(PISDN_ADAPTER IoAdapter,
			dword start_address, dword features)
{
	volatile word __iomem *signature;
	int started = 0;
	int i;
	byte __iomem *p;


	start_qBri_hardware(IoAdapter);

	p = DIVA_OS_MEM_ATTACH_RAM(IoAdapter);


	signature = (volatile word __iomem *) (&p[0x1E]);

	for (i = 0; i < 300; ++i) {
		diva_os_wait(10);
		if (READ_WORD(&signature[0]) == 0x4447) {
			DBG_TRC(("Protocol startup time %d.%02d seconds",
				 (i / 100), (i % 100)))
				started = 1;
			break;
		}
	}

	for (i = 1; i < IoAdapter->tasks; i++) {
		IoAdapter->QuadroList->QuadroAdapter[i]->features =
			IoAdapter->features;
		IoAdapter->QuadroList->QuadroAdapter[i]->a.
			protocol_capabilities = IoAdapter->features;
	}

	if (!started) {
		DBG_FTL(("%s: Adapter selftest failed, signature=%04x",
			 IoAdapter->Properties.Name,
			 READ_WORD(&signature[0])))
			DIVA_OS_MEM_DETACH_RAM(IoAdapter, p);
		(*(IoAdapter->trapFnc)) (IoAdapter);
		IoAdapter->stop(IoAdapter);
		return (-1);
	}
	DIVA_OS_MEM_DETACH_RAM(IoAdapter, p);

	for (i = 0; i < IoAdapter->tasks; i++) {
		IoAdapter->QuadroList->QuadroAdapter[i]->Initialized = 1;
		IoAdapter->QuadroList->QuadroAdapter[i]->IrqCount = 0;
	}

	if (check_qBri_interrupt(IoAdapter)) {
		DBG_ERR(("A: A(%d) interrupt test failed",
			 IoAdapter->ANum))
			for (i = 0; i < IoAdapter->tasks; i++) {
				IoAdapter->QuadroList->QuadroAdapter[i]->Initialized = 0;
			}
		IoAdapter->stop(IoAdapter);
		return (-1);
	}

	IoAdapter->Properties.Features = (word) features;
	diva_xdi_display_adapter_features(IoAdapter->ANum);

	for (i = 0; i < IoAdapter->tasks; i++) {
		DBG_LOG(("A(%d) %s adapter successfully started",
			 IoAdapter->QuadroList->QuadroAdapter[i]->ANum,
			 (IoAdapter->tasks == 1) ? "BRI 2.0" : "4BRI"))
			diva_xdi_didd_register_adapter(IoAdapter->QuadroList->QuadroAdapter[i]->ANum);
		IoAdapter->QuadroList->QuadroAdapter[i]->Properties.Features = (word) features;
	}

	return (0);
}
