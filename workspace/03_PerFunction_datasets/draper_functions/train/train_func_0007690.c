nvt_cir_wake_isr(int irq, void *data)
{
	u8 status, iren, val;
	struct nvt_dev *nvt = data;
	unsigned long flags;

	nvt_dbg_wake("%s firing", __func__);

	status = nvt_cir_wake_reg_read(nvt, CIR_WAKE_IRSTS);
	if (!status)
		return IRQ_RETVAL(IRQ_NONE);

	if (status & CIR_WAKE_IRSTS_IR_PENDING)
		nvt_clear_cir_wake_fifo(nvt);

	nvt_cir_wake_reg_write(nvt, status, CIR_WAKE_IRSTS);
	nvt_cir_wake_reg_write(nvt, 0, CIR_WAKE_IRSTS);


	iren = nvt_cir_wake_reg_read(nvt, CIR_WAKE_IREN);
	if (!iren) {
		nvt_dbg_wake("%s exiting, wake not enabled", __func__);
		return IRQ_RETVAL(IRQ_HANDLED);
	}

	if ((status & CIR_WAKE_IRSTS_PE) &&
	    (nvt->wake_state == ST_WAKE_START)) {
		while (nvt_cir_wake_reg_read(nvt, CIR_WAKE_RD_FIFO_ONLY_IDX)) {
			val = nvt_cir_wake_reg_read(nvt, CIR_WAKE_RD_FIFO_ONLY);
			nvt_dbg("setting wake up key: 0x%x", val);
		}

		nvt_cir_wake_reg_write(nvt, 0, CIR_WAKE_IREN);
		spin_lock_irqsave(&nvt->nvt_lock, flags);
		nvt->wake_state = ST_WAKE_FINISH;
		spin_unlock_irqrestore(&nvt->nvt_lock, flags);
	}

	nvt_dbg_wake("%s done", __func__);
	return IRQ_RETVAL(IRQ_HANDLED);
}
