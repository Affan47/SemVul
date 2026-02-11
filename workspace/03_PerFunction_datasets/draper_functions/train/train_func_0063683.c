t4vf_wr_mbox_core(struct adapter *adapter, const void *cmd, int size,
		      void *rpl, bool sleep_ok)
{
	static const int delay[] = {
		1, 1, 3, 5, 10, 10, 20, 50, 100
	};

	u32 v;
	int i, ms, delay_idx;
	const __be64 *p;
	u32 mbox_data = T4VF_MBDATA_BASE_ADDR;
	u32 mbox_ctl = T4VF_CIM_BASE_ADDR + CIM_VF_EXT_MAILBOX_CTRL;


	if ((size % 16) != 0 ||
	    size > NUM_CIM_VF_MAILBOX_DATA_INSTANCES * 4)
		return -EINVAL;


	v = MBOWNER_G(t4_read_reg(adapter, mbox_ctl));
	for (i = 0; v == MBOX_OWNER_NONE && i < 3; i++)
		v = MBOWNER_G(t4_read_reg(adapter, mbox_ctl));
	if (v != MBOX_OWNER_DRV)
		return v == MBOX_OWNER_FW ? -EBUSY : -ETIMEDOUT;


	for (i = 0, p = cmd; i < size; i += 8)
		t4_write_reg64(adapter, mbox_data + i, be64_to_cpu(*p++));
	t4_read_reg(adapter, mbox_data);

	t4_write_reg(adapter, mbox_ctl,
		     MBMSGVALID_F | MBOWNER_V(MBOX_OWNER_FW));
	t4_read_reg(adapter, mbox_ctl);


	delay_idx = 0;
	ms = delay[0];

	for (i = 0; i < FW_CMD_MAX_TIMEOUT; i += ms) {
		if (sleep_ok) {
			ms = delay[delay_idx];
			if (delay_idx < ARRAY_SIZE(delay) - 1)
				delay_idx++;
			msleep(ms);
		} else
			mdelay(ms);


		v = t4_read_reg(adapter, mbox_ctl);
		if (MBOWNER_G(v) == MBOX_OWNER_DRV) {


			if ((v & MBMSGVALID_F) == 0) {
				t4_write_reg(adapter, mbox_ctl,
					     MBOWNER_V(MBOX_OWNER_NONE));
				continue;
			}


			v = t4_read_reg(adapter, mbox_data);
			if (FW_CMD_RETVAL_G(v))
				dump_mbox(adapter, "FW Error", mbox_data);

			if (rpl) {

				WARN_ON((be32_to_cpu(*(const __be32 *)cmd)
					 & FW_CMD_REQUEST_F) == 0);
				get_mbox_rpl(adapter, rpl, size, mbox_data);
				WARN_ON((be32_to_cpu(*(__be32 *)rpl)
					 & FW_CMD_REQUEST_F) != 0);
			}
			t4_write_reg(adapter, mbox_ctl,
				     MBOWNER_V(MBOX_OWNER_NONE));
			return -FW_CMD_RETVAL_G(v);
		}
	}


	dump_mbox(adapter, "FW Timeout", mbox_data);
	return -ETIMEDOUT;
}
