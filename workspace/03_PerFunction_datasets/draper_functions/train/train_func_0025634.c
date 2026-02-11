xen_event_channel_op_compat(int cmd, void *arg)
{
	struct evtchn_op op;
	int rc;

	op.cmd = cmd;
	memcpy(&op.u, arg, sizeof(op.u));
	rc = _hypercall1(int, event_channel_op_compat, &op);

	switch (cmd) {
	case EVTCHNOP_close:
	case EVTCHNOP_send:
	case EVTCHNOP_bind_vcpu:
	case EVTCHNOP_unmask:

		break;

#define COPY_BACK(eop) \
	case EVTCHNOP_##eop: \
		memcpy(arg, &op.u.eop, sizeof(op.u.eop)); \
		break

	COPY_BACK(bind_interdomain);
	COPY_BACK(bind_virq);
	COPY_BACK(bind_pirq);
	COPY_BACK(status);
	COPY_BACK(alloc_unbound);
	COPY_BACK(bind_ipi);
#undef COPY_BACK

	default:
		WARN_ON(rc != -ENOSYS);
		break;
	}

	return rc;
}
