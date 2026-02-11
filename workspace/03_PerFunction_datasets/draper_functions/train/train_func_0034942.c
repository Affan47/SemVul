be_intx(int irq, void *dev)
{
	struct be_eq_obj *eqo = dev;
	struct be_adapter *adapter = eqo->adapter;
	int num_evts = 0;


	if (napi_schedule_prep(&eqo->napi)) {
		num_evts = events_get(eqo);
		__napi_schedule(&eqo->napi);
		if (num_evts)
			eqo->spurious_intr = 0;
	}
	be_eq_notify(adapter, eqo->q.id, false, true, num_evts, 0);


	if (num_evts || eqo->spurious_intr++ == 0)
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}
