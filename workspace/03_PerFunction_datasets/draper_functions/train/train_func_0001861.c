smi_ir_irq(struct smi_rc *ir, u32 int_status)
{
	int handled = 0;

	if (int_status & IR_X_INT) {
		smi_ir_disableInterrupt(ir);
		smi_ir_clearInterrupt(ir);
		schedule_work(&ir->work);
		handled = 1;
	}
	return handled;
}
