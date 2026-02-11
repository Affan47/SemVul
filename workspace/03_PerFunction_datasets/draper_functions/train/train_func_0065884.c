fc_tprlo_build(struct fchs_s *fchs, u32 d_id, u32 s_id, u16 ox_id,
	       int num_pages, enum fc_tprlo_type tprlo_type, u32 tpr_id)
{
	struct fc_tprlo_s *tprlo = (struct fc_tprlo_s *) (fchs + 1);
	int             page;

	fc_els_req_build(fchs, d_id, s_id, ox_id);
	memset(tprlo, 0, (num_pages * 16) + 4);
	tprlo->command = FC_ELS_TPRLO;
	tprlo->page_len = 0x10;
	tprlo->payload_len = cpu_to_be16((num_pages * 16) + 4);

	for (page = 0; page < num_pages; page++) {
		tprlo->tprlo_params[page].type = FC_TYPE_FCP;
		tprlo->tprlo_params[page].opa_valid = 0;
		tprlo->tprlo_params[page].rpa_valid = 0;
		tprlo->tprlo_params[page].orig_process_assc = 0;
		tprlo->tprlo_params[page].resp_process_assc = 0;
		if (tprlo_type == FC_GLOBAL_LOGO) {
			tprlo->tprlo_params[page].global_process_logout = 1;
		} else if (tprlo_type == FC_TPR_LOGO) {
			tprlo->tprlo_params[page].tpo_nport_valid = 1;
			tprlo->tprlo_params[page].tpo_nport_id = (tpr_id);
		}
	}

	return be16_to_cpu(tprlo->payload_len);
}
