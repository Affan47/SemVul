auth_mgr_release_auth_handle(TCS_AUTHHANDLE tpm_auth_handle, TCS_CONTEXT_HANDLE tcs_handle,
			     TSS_BOOL cont)
{
	UINT32 i;
	TSS_RESULT result = TSS_SUCCESS;

	for (i = 0; i < auth_mgr.auth_mapper_size; i++) {
		if (auth_mgr.auth_mapper[i].full == TRUE &&
		    auth_mgr.auth_mapper[i].tpm_handle == tpm_auth_handle &&
		    auth_mgr.auth_mapper[i].tcs_ctx == tcs_handle) {
			if (!cont) {


                               result = TCSP_FlushSpecific_Common(
                                   auth_mgr.auth_mapper[i].tpm_handle,
                                   TPM_RT_AUTH);


				if (result == TPM_E_BAD_ORDINAL)
                                       result = internal_TerminateHandle(
                                           auth_mgr.auth_mapper[i].tpm_handle);

				if (result == TCPA_E_INVALID_AUTHHANDLE) {
					LogDebug("Tried to close an invalid auth handle: %x",
						 auth_mgr.auth_mapper[i].tpm_handle);
				} else if (result != TCPA_SUCCESS) {
					LogDebug("TPM_TerminateHandle returned %d", result);
				}

                               if (result == TPM_SUCCESS) {
                                       LogDebug("released auth for TCS %x TPM %x",
                                                auth_mgr.auth_mapper[i].tcs_ctx, tpm_auth_handle);
                               }


                               auth_mgr.open_auth_sessions--;
                               auth_mgr.auth_mapper[i].full = FALSE;
                               auth_mgr.auth_mapper[i].tpm_handle = 0;
                               auth_mgr.auth_mapper[i].tcs_ctx = 0;
                               auth_mgr_swap_in();
			}

		}
	}

	return result;
}
