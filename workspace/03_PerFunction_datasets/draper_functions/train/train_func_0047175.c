put_ir_tx(struct IR_tx *tx, bool ir_devices_lock_held)
{
	int released;
	struct IR *ir = tx->ir;

	spin_lock(&ir->tx_ref_lock);
	released = kref_put(&tx->ref, release_ir_tx);
	spin_unlock(&ir->tx_ref_lock);

	if (released)
		put_ir_device(ir, ir_devices_lock_held);
	return released;
}
