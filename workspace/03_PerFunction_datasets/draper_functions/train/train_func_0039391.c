nvt_cir_isr(int irq, void *data)
{
	struct nvt_dev *nvt = data;
	u8 status, iren, cur_state;
	unsigned long flags;

	nvt_dbg_verbose("%s firing", __func__);

	nvt_efm_enable(nvt);
	nvt_select_logical_dev(nvt, LOGICAL_DEV_CIR);
	nvt_efm_disable(nvt);


	status = nvt_cir_reg_read(nvt, CIR_IRSTS);
	if (!status) {
		nvt_dbg_verbose("%s exiting, IRSTS 0x0", __func__);
		nvt_cir_reg_write(nvt, 0xff, CIR_IRSTS);
		return IRQ_RETVAL(IRQ_NONE);
	}


	nvt_cir_reg_write(nvt, status, CIR_IRSTS);
	nvt_cir_reg_write(nvt, 0, CIR_IRSTS);


	iren = nvt_cir_reg_read(nvt, CIR_IREN);
	if (!iren) {
		nvt_dbg_verbose("%s exiting, CIR not enabled", __func__);
		return IRQ_RETVAL(IRQ_NONE);
	}

	if (debug)
		nvt_cir_log_irqs(status, iren);

	if (status & CIR_IRSTS_RTR) {


		if (nvt_cir_tx_inactive(nvt))
			nvt_get_rx_ir_data(nvt);
	}

	if (status & CIR_IRSTS_PE) {
		if (nvt_cir_tx_inactive(nvt))
			nvt_get_rx_ir_data(nvt);

		spin_lock_irqsave(&nvt->nvt_lock, flags);

		cur_state = nvt->study_state;

		spin_unlock_irqrestore(&nvt->nvt_lock, flags);

		if (cur_state == ST_STUDY_NONE)
			nvt_clear_cir_fifo(nvt);
	}

	if (status & CIR_IRSTS_TE)
		nvt_clear_tx_fifo(nvt);

	if (status & CIR_IRSTS_TTR) {
		unsigned int pos, count;
		u8 tmp;

		spin_lock_irqsave(&nvt->tx.lock, flags);

		pos = nvt->tx.cur_buf_num;
		count = nvt->tx.buf_count;


		if (pos < count) {
			nvt_cir_reg_write(nvt, nvt->tx.buf[pos], CIR_STXFIFO);
			nvt->tx.cur_buf_num++;

		} else {
			tmp = nvt_cir_reg_read(nvt, CIR_IREN);
			nvt_cir_reg_write(nvt, tmp & ~CIR_IREN_TTR, CIR_IREN);
		}

		spin_unlock_irqrestore(&nvt->tx.lock, flags);

	}

	if (status & CIR_IRSTS_TFU) {
		spin_lock_irqsave(&nvt->tx.lock, flags);
		if (nvt->tx.tx_state == ST_TX_REPLY) {
			nvt->tx.tx_state = ST_TX_REQUEST;
			wake_up(&nvt->tx.queue);
		}
		spin_unlock_irqrestore(&nvt->tx.lock, flags);
	}

	nvt_dbg_verbose("%s done", __func__);
	return IRQ_RETVAL(IRQ_HANDLED);
}
