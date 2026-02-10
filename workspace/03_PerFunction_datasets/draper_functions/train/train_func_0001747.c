recv_pma_get_portcounters_ext(struct ib_pma_mad *pmp,
					 struct ib_device *ibdev, u8 port)
{
	struct ib_pma_portcounters_ext *p =
		(struct ib_pma_portcounters_ext *)pmp->data;
	struct ipath_ibdev *dev = to_idev(ibdev);
	u64 swords, rwords, spkts, rpkts, xwait;
	u8 port_select = p->port_select;

	ipath_snapshot_counters(dev->dd, &swords, &rwords, &spkts,
				&rpkts, &xwait);


	swords -= dev->z_port_xmit_data;
	rwords -= dev->z_port_rcv_data;
	spkts -= dev->z_port_xmit_packets;
	rpkts -= dev->z_port_rcv_packets;

	memset(pmp->data, 0, sizeof(pmp->data));

	p->port_select = port_select;
	if (pmp->mad_hdr.attr_mod != 0 ||
	    (port_select != port && port_select != 0xFF))
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;

	p->port_xmit_data = cpu_to_be64(swords);
	p->port_rcv_data = cpu_to_be64(rwords);
	p->port_xmit_packets = cpu_to_be64(spkts);
	p->port_rcv_packets = cpu_to_be64(rpkts);
	p->port_unicast_xmit_packets = cpu_to_be64(dev->n_unicast_xmit);
	p->port_unicast_rcv_packets = cpu_to_be64(dev->n_unicast_rcv);
	p->port_multicast_xmit_packets = cpu_to_be64(dev->n_multicast_xmit);
	p->port_multicast_rcv_packets = cpu_to_be64(dev->n_multicast_rcv);

	return reply((struct ib_smp *) pmp);
}
