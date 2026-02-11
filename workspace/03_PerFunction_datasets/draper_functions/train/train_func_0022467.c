stk7700p_pid_filter(struct dvb_usb_adapter *adapter, int index,
		u16 pid, int onoff)
{
	struct dib0700_adapter_state *state = adapter->priv;
	struct dib0700_state *st = adapter->dev->priv;

	if (st->is_dib7000pc)
		return state->dib7000p_ops.pid_filter(adapter->fe_adap[0].fe, index, pid, onoff);
	return dib7000m_pid_filter(adapter->fe_adap[0].fe, index, pid, onoff);
}
