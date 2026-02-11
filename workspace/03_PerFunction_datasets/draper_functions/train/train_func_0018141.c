cxgbi_iscsi_cleanup(struct iscsi_transport *itp,
			struct scsi_transport_template **stt)
{
	if (*stt) {
		log_debug(1 << CXGBI_DBG_ISCSI,
			"de-register transport 0x%p, %s, stt 0x%p.\n",
			itp, itp->name, *stt);
		*stt = NULL;
		iscsi_unregister_transport(itp);
	}
}
