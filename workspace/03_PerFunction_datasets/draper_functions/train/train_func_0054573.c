efx_ef10_sriov_set_vf_link_state(struct efx_nic *efx, int vf_i,
				     int link_state)
{
	MCDI_DECLARE_BUF(inbuf, MC_CMD_LINK_STATE_MODE_IN_LEN);
	struct efx_ef10_nic_data *nic_data = efx->nic_data;

	BUILD_BUG_ON(IFLA_VF_LINK_STATE_AUTO !=
		     MC_CMD_LINK_STATE_MODE_IN_LINK_STATE_AUTO);
	BUILD_BUG_ON(IFLA_VF_LINK_STATE_ENABLE !=
		     MC_CMD_LINK_STATE_MODE_IN_LINK_STATE_UP);
	BUILD_BUG_ON(IFLA_VF_LINK_STATE_DISABLE !=
		     MC_CMD_LINK_STATE_MODE_IN_LINK_STATE_DOWN);
	MCDI_POPULATE_DWORD_2(inbuf, LINK_STATE_MODE_IN_FUNCTION,
			      LINK_STATE_MODE_IN_FUNCTION_PF,
			      nic_data->pf_index,
			      LINK_STATE_MODE_IN_FUNCTION_VF, vf_i);
	MCDI_SET_DWORD(inbuf, LINK_STATE_MODE_IN_NEW_MODE, link_state);
	return efx_mcdi_rpc(efx, MC_CMD_LINK_STATE_MODE, inbuf, sizeof(inbuf),
			    NULL, 0, NULL);
}
