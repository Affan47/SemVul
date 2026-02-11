hba_ioctl_done_callback(struct esas2r_adapter *a,
				    struct esas2r_request *rq, void *context)
{
	struct atto_ioctl *ioctl_hba =
		(struct atto_ioctl *)esas2r_buffered_ioctl;

	esas2r_debug("hba_ioctl_done_callback %d", a->index);

	if (ioctl_hba->function == ATTO_FUNC_GET_ADAP_INFO) {
		struct atto_hba_get_adapter_info *gai =
			&ioctl_hba->data.get_adap_info;

		esas2r_debug("ATTO_FUNC_GET_ADAP_INFO");

		gai->drvr_rev_major = ESAS2R_MAJOR_REV;
		gai->drvr_rev_minor = ESAS2R_MINOR_REV;

		strcpy(gai->drvr_rev_ascii, ESAS2R_VERSION_STR);
		strcpy(gai->drvr_name, ESAS2R_DRVR_NAME);

		gai->num_busses = 1;
		gai->num_targsper_bus = ESAS2R_MAX_ID + 1;
		gai->num_lunsper_targ = 1;
	}
}
