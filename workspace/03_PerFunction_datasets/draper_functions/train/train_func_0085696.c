__subn_get_opa_led_info(struct opa_smp *smp, u32 am, u8 *data,
				   struct ib_device *ibdev, u8 port,
				   u32 *resp_len)
{
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	struct opa_led_info *p = (struct opa_led_info *) data;
	u32 nport = OPA_AM_NPORT(am);
	u64 reg;

	if (nport != 1 || OPA_AM_PORTNUM(am)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	reg = read_csr(dd, DCC_CFG_LED_CNTRL);
	if ((reg & DCC_CFG_LED_CNTRL_LED_CNTRL_SMASK) &&
		((reg & DCC_CFG_LED_CNTRL_LED_SW_BLINK_RATE_SMASK) == 0xf))
			p->rsvd_led_mask = cpu_to_be32(OPA_LED_MASK);

	if (resp_len)
		*resp_len += sizeof(struct opa_led_info);

	return reply((struct ib_mad_hdr *)smp);
}
