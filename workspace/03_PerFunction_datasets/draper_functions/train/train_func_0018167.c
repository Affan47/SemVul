ipmi_mc_get_selftest(struct ipmi_intf * intf)
{
   int rv = 0;
	struct ipmi_rs * rsp;
	struct ipmi_rq req;
	struct ipm_selftest_rsp *sft_res;

	memset(&req, 0, sizeof(req));
	req.msg.netfn = IPMI_NETFN_APP;
	req.msg.cmd = BMC_GET_SELF_TEST;
	req.msg.data_len = 0;

	rsp = intf->sendrecv(intf, &req);
	if (!rsp) {
		lprintf(LOG_ERR, "No response from devices\n");
		return -1;
	}

	if (rsp->ccode) {
		lprintf(LOG_ERR, "Bad response: (%s)",
				val2str(rsp->ccode, completion_code_vals));
		return -1;
	}

	sft_res = (struct ipm_selftest_rsp *) rsp->data;

	if (sft_res->code == IPM_SFT_CODE_OK) {
		printf("Selftest: passed\n");
		rv = 0;
	}

	else if (sft_res->code == IPM_SFT_CODE_NOT_IMPLEMENTED) {
		printf("Selftest: not implemented\n");
		rv = -1;
	}

	else if (sft_res->code == IPM_SFT_CODE_DEV_CORRUPTED) {
		printf("Selftest: device corrupted\n");
		rv = -1;

		if (sft_res->test & IPM_SELFTEST_SEL_ERROR) {
			printf(" -> SEL device not accessible\n");
		}
		if (sft_res->test & IPM_SELFTEST_SDR_ERROR) {
			printf(" -> SDR repository not accesible\n");
		}
		if (sft_res->test & IPM_SELFTEST_FRU_ERROR) {
			printf("FRU device not accessible\n");
		}
		if (sft_res->test & IPM_SELFTEST_IPMB_ERROR) {
			printf("IPMB signal lines do not respond\n");
		}
		if (sft_res->test & IPM_SELFTEST_SDRR_EMPTY) {
			printf("SDR repository empty\n");
		}
		if (sft_res->test & IPM_SELFTEST_INTERNAL_USE) {
			printf("Internal Use Area corrupted\n");
		}
		if (sft_res->test & IPM_SELFTEST_FW_BOOTBLOCK) {
			printf("Controller update boot block corrupted\n");
		}
		if (sft_res->test & IPM_SELFTEST_FW_CORRUPTED) {
			printf("controller operational firmware corrupted\n");
		}
	}

	else if (sft_res->code == IPM_SFT_CODE_FATAL_ERROR) {
		printf("Selftest     : fatal error\n");
		printf("Failure code : %02x\n", sft_res->test);
		rv = -1;
	}

	else if (sft_res->code == IPM_SFT_CODE_RESERVED) {
		printf("Selftest: N/A");
		rv = -1;
	}

	else {
		printf("Selftest     : device specific (%02Xh)\n", sft_res->code);
		printf("Failure code : %02Xh\n", sft_res->test);
		rv = 0;
	}

	return rv;
}
