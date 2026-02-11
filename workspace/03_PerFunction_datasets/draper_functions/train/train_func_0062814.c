ddns_fwd_srv_rem1(dhcp_ddns_cb_t *ddns_cb,
		  isc_result_t    eresult)
{
	isc_result_t result = eresult;
	char ddns_address[MAX_ADDRESS_STRING_LEN];

	switch(eresult) {
	case ISC_R_SUCCESS:

		strcpy(ddns_address, piaddr(ddns_cb->address));
		log_info("Removed forward map from %.*s to %s",
			 (int)ddns_cb->fwd_name.len,
			 (const char*)ddns_cb->fwd_name.data,
			 ddns_address);


		ddns_cb->state    = DDNS_STATE_REM_FW_NXRR;
		ddns_cb->cur_func = ddns_fwd_srv_rem2;
		result = ddns_modify_fwd(ddns_cb, MDL);
		if (result == ISC_R_SUCCESS) {
			return;
		}
		break;

	case DNS_R_NXRRSET:
	case DNS_R_NXDOMAIN:
		ddns_update_lease_text(ddns_cb, NULL);

#if defined (DEBUG_DNS_UPDATES)
		log_info("DDNS: no forward map to remove. %p", ddns_cb);
#endif


		if ((ddns_cb->flags & DDNS_UPDATE_PTR) != 0) {

			if (ddns_cb->zone != NULL) {
				ddns_cb_forget_zone(ddns_cb);
			}

			ddns_cb->state    = DDNS_STATE_REM_PTR;
			ddns_cb->cur_func = ddns_ptr_remove;

			result = ddns_modify_ptr(ddns_cb, MDL);
			if (result == ISC_R_SUCCESS) {
				return;
			}
		}
		else {

			eresult = ISC_R_SUCCESS;
		}
		break;

	default:
		break;
	}

	ddns_update_lease_ptr(NULL, NULL, ddns_cb, NULL, MDL);
	ddns_fwd_srv_connector(NULL, NULL, NULL, ddns_cb->next_op, eresult);
	ddns_cb_free(ddns_cb, MDL);
}
