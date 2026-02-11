pma_get_classportinfo(struct ib_pma_mad *pmp,
				 struct ib_device *ibdev)
{
	struct ib_class_port_info *p =
		(struct ib_class_port_info *)pmp->data;
	struct qib_devdata *dd = dd_from_ibdev(ibdev);

	memset(pmp->data, 0, sizeof(pmp->data));

	if (pmp->mad_hdr.attr_mod != 0)
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;


	p->base_version = 1;
	p->class_version = 1;
	p->capability_mask = IB_PMA_CLASS_CAP_EXT_WIDTH;


	p->reserved[0] = dd->psxmitwait_supported << 7;


	p->resp_time_value = 18;

	return reply((struct ib_smp *) pmp);
}
