qib_send_trap(struct qib_ibport *ibp, void *data, unsigned len)
{
	struct ib_mad_send_buf *send_buf;
	struct ib_mad_agent *agent;
	struct ib_smp *smp;
	int ret;
	unsigned long flags;
	unsigned long timeout;

	agent = ibp->send_agent;
	if (!agent)
		return;


	if (!(ppd_from_ibp(ibp)->lflags & QIBL_LINKACTIVE))
		return;


	if (ibp->trap_timeout && time_before(jiffies, ibp->trap_timeout))
		return;

	send_buf = ib_create_send_mad(agent, 0, 0, 0, IB_MGMT_MAD_HDR,
				      IB_MGMT_MAD_DATA, GFP_ATOMIC,
				      IB_MGMT_BASE_VERSION);
	if (IS_ERR(send_buf))
		return;

	smp = send_buf->mad;
	smp->base_version = IB_MGMT_BASE_VERSION;
	smp->mgmt_class = IB_MGMT_CLASS_SUBN_LID_ROUTED;
	smp->class_version = 1;
	smp->method = IB_MGMT_METHOD_TRAP;
	ibp->tid++;
	smp->tid = cpu_to_be64(ibp->tid);
	smp->attr_id = IB_SMP_ATTR_NOTICE;

	memcpy(smp->data, data, len);

	spin_lock_irqsave(&ibp->lock, flags);
	if (!ibp->sm_ah) {
		if (ibp->sm_lid != be16_to_cpu(IB_LID_PERMISSIVE)) {
			struct ib_ah *ah;

			ah = qib_create_qp0_ah(ibp, ibp->sm_lid);
			if (IS_ERR(ah))
				ret = PTR_ERR(ah);
			else {
				send_buf->ah = ah;
				ibp->sm_ah = to_iah(ah);
				ret = 0;
			}
		} else
			ret = -EINVAL;
	} else {
		send_buf->ah = &ibp->sm_ah->ibah;
		ret = 0;
	}
	spin_unlock_irqrestore(&ibp->lock, flags);

	if (!ret)
		ret = ib_post_send_mad(send_buf, NULL);
	if (!ret) {

		timeout = (4096 * (1UL << ibp->subnet_timeout)) / 1000;
		ibp->trap_timeout = jiffies + usecs_to_jiffies(timeout);
	} else {
		ib_free_send_mad(send_buf);
		ibp->trap_timeout = 0;
	}
}
