be_mgmt_get_boot_shandle(struct beiscsi_hba *phba,
			      unsigned int *s_handle)
{
	struct be_cmd_get_boot_target_resp *boot_resp;
	struct be_mcc_wrb *wrb;
	unsigned int tag;
	uint8_t boot_retry = 3;
	int rc;

	do {

		tag = mgmt_get_boot_target(phba);
		if (!tag) {
			beiscsi_log(phba, KERN_ERR,
				    BEISCSI_LOG_CONFIG | BEISCSI_LOG_INIT,
				    "BG_%d : Getting Boot Target Info Failed\n");
			return -EAGAIN;
		}

		rc = beiscsi_mccq_compl(phba, tag, &wrb, NULL);
		if (rc) {
			beiscsi_log(phba, KERN_ERR,
				    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
				    "BG_%d : MBX CMD get_boot_target Failed\n");
			return -EBUSY;
		}

		boot_resp = embedded_payload(wrb);


		if (!boot_resp->boot_session_count) {
			beiscsi_log(phba, KERN_INFO,
				    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
				    "BG_%d  ;No boot targets configured\n");
			return -ENXIO;
		}


		if (boot_resp->boot_session_handle != INVALID_SESS_HANDLE) {
			*s_handle = boot_resp->boot_session_handle;
			return 0;
		}


		tag = mgmt_reopen_session(phba, BE_REOPEN_BOOT_SESSIONS,
					  INVALID_SESS_HANDLE);
		if (!tag) {
			beiscsi_log(phba, KERN_ERR,
				    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
				    "BG_%d : mgmt_reopen_session Failed\n");
			return -EAGAIN;
		}

		rc = beiscsi_mccq_compl(phba, tag, NULL, NULL);
		if (rc) {
			beiscsi_log(phba, KERN_ERR,
				    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
				    "BG_%d : mgmt_reopen_session Failed");
			return rc;
		}
	} while (--boot_retry);


	beiscsi_log(phba, KERN_ERR,
		    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
		    "BG_%d : Login to Boot Target Failed\n");
	return -ENXIO;
}
