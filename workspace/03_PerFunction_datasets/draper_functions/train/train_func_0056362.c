au0828_rc_stop(struct rc_dev *rc)
{
	struct au0828_rc *ir = rc->priv;

	cancel_delayed_work_sync(&ir->work);


	if (!test_bit(DEV_DISCONNECTED, &ir->dev->dev_state)) {

		au8522_rc_clear(ir, 0xe0, 1 << 4);
	}
}
