bnx2i_start(void *handle)
{
#define BNX2I_INIT_POLL_TIME	(1000 / HZ)
	struct bnx2i_hba *hba = handle;
	int i = HZ;


	bnx2i_send_fw_iscsi_init_msg(hba);
	while (!test_bit(ADAPTER_STATE_UP, &hba->adapter_state) &&
	       !test_bit(ADAPTER_STATE_INIT_FAILED, &hba->adapter_state) && i--)
		msleep(BNX2I_INIT_POLL_TIME);
}
