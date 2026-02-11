pma_get_opa_errorinfo(struct opa_pma_mad *pmp,
			struct ib_device *ibdev, u8 port, u32 *resp_len)
{
	size_t response_data_size;
	struct _port_ei *rsp;
	struct opa_port_error_info_msg *req;
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u64 port_mask;
	u32 num_ports;
	unsigned long port_num;
	u8 num_pslm;
	u64 reg;

	req = (struct opa_port_error_info_msg *)pmp->data;
	rsp = (struct _port_ei *)&(req->port[0]);

	num_ports = OPA_AM_NPORT(be32_to_cpu(pmp->mad_hdr.attr_mod));
	num_pslm = hweight64(be64_to_cpu(req->port_select_mask[3]));

	memset(rsp, 0, sizeof(*rsp));

	if (num_ports != 1 || num_ports != num_pslm) {
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)pmp);
	}


	response_data_size = sizeof(struct opa_port_error_info_msg);

	if (response_data_size > sizeof(pmp->data)) {
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)pmp);
	}


	port_mask = be64_to_cpu(req->port_select_mask[3]);
	port_num = find_first_bit((unsigned long *)&port_mask,
				  sizeof(port_mask));

	if ((u8)port_num != port) {
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)pmp);
	}


	rsp->port_rcv_ei.status_and_code =
		dd->err_info_rcvport.status_and_code;
	memcpy(&rsp->port_rcv_ei.ei.ei1to12.packet_flit1,
		&dd->err_info_rcvport.packet_flit1, sizeof(u64));
	memcpy(&rsp->port_rcv_ei.ei.ei1to12.packet_flit2,
		&dd->err_info_rcvport.packet_flit2, sizeof(u64));


	reg = read_csr(dd, RCV_ERR_INFO);
	if (reg & RCV_ERR_INFO_RCV_EXCESS_BUFFER_OVERRUN_SMASK) {


		u8 tmp = (u8)reg;

		tmp &=  RCV_ERR_INFO_RCV_EXCESS_BUFFER_OVERRUN_SC_SMASK;
		tmp <<= 2;
		rsp->excessive_buffer_overrun_ei.status_and_sc = tmp;

		rsp->excessive_buffer_overrun_ei.status_and_sc |= 0x80;
	}

	rsp->port_xmit_constraint_ei.status =
		dd->err_info_xmit_constraint.status;
	rsp->port_xmit_constraint_ei.pkey =
		cpu_to_be16(dd->err_info_xmit_constraint.pkey);
	rsp->port_xmit_constraint_ei.slid =
		cpu_to_be32(dd->err_info_xmit_constraint.slid);

	rsp->port_rcv_constraint_ei.status =
		dd->err_info_rcv_constraint.status;
	rsp->port_rcv_constraint_ei.pkey =
		cpu_to_be16(dd->err_info_rcv_constraint.pkey);
	rsp->port_rcv_constraint_ei.slid =
		cpu_to_be32(dd->err_info_rcv_constraint.slid);


	rsp->uncorrectable_ei.status_and_code = dd->err_info_uncorrectable;


	rsp->fm_config_ei.status_and_code = dd->err_info_fmconfig;

	if (resp_len)
		*resp_len += response_data_size;

	return reply((struct ib_mad_hdr *)pmp);
}
