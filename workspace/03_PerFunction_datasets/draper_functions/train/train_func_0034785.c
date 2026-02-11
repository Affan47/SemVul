bfad_im_fc_rport_add(struct bfad_im_port_s *im_port, struct bfad_itnim_s *itnim)
{
	struct fc_rport_identifiers rport_ids;
	struct fc_rport *fc_rport;
	struct bfad_itnim_data_s *itnim_data;

	rport_ids.node_name =
		cpu_to_be64(bfa_fcs_itnim_get_nwwn(&itnim->fcs_itnim));
	rport_ids.port_name =
		cpu_to_be64(bfa_fcs_itnim_get_pwwn(&itnim->fcs_itnim));
	rport_ids.port_id =
		bfa_hton3b(bfa_fcs_itnim_get_fcid(&itnim->fcs_itnim));
	rport_ids.roles = FC_RPORT_ROLE_UNKNOWN;

	itnim->fc_rport = fc_rport =
		fc_remote_port_add(im_port->shost, 0, &rport_ids);

	if (!fc_rport)
		return;

	fc_rport->maxframe_size =
		bfa_fcs_itnim_get_maxfrsize(&itnim->fcs_itnim);
	fc_rport->supported_classes = bfa_fcs_itnim_get_cos(&itnim->fcs_itnim);

	itnim_data = fc_rport->dd_data;
	itnim_data->itnim = itnim;

	rport_ids.roles |= FC_RPORT_ROLE_FCP_TARGET;

	if (rport_ids.roles != FC_RPORT_ROLE_UNKNOWN)
		fc_remote_port_rolechg(fc_rport, rport_ids.roles);

	if ((fc_rport->scsi_target_id != -1)
	    && (fc_rport->scsi_target_id < MAX_FCP_TARGET))
		itnim->scsi_tgt_id = fc_rport->scsi_target_id;

	itnim->channel = fc_rport->channel;

	return;
}
