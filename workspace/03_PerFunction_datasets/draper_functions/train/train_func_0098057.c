wil6210_irq_misc_thread(int irq, void *cookie)
{
	struct wil6210_priv *wil = cookie;
	u32 isr = wil->isr_misc;

	trace_wil6210_irq_misc_thread(isr);
	wil_dbg_irq(wil, "Thread ISR MISC 0x%08x\n", isr);

	if (isr & ISR_MISC_FW_ERROR) {
		wil_fw_core_dump(wil);
		wil_notify_fw_error(wil);
		isr &= ~ISR_MISC_FW_ERROR;
		wil_fw_error_recovery(wil);
	}

	if (isr & ISR_MISC_MBOX_EVT) {
		wil_dbg_irq(wil, "MBOX event\n");
		wmi_recv_cmd(wil);
		isr &= ~ISR_MISC_MBOX_EVT;
	}

	if (isr)
		wil_dbg_irq(wil, "un-handled MISC ISR bits 0x%08x\n", isr);

	wil->isr_misc = 0;

	wil6210_unmask_irq_misc(wil);

	return IRQ_HANDLED;
}
