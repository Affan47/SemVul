cnic_bnx2x_iscsi_update(struct cnic_dev *dev, struct kwqe *kwqe)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct iscsi_kwqe_conn_update *req =
		(struct iscsi_kwqe_conn_update *) kwqe;
	void *data;
	union l5cm_specific_data l5_data;
	u32 l5_cid, cid = BNX2X_SW_CID(req->context_id);
	int ret;

	if (cnic_get_l5_cid(cp, cid, &l5_cid) != 0)
		return -EINVAL;

	data = cnic_get_kwqe_16_data(cp, l5_cid, &l5_data);
	if (!data)
		return -ENOMEM;

	memcpy(data, kwqe, sizeof(struct kwqe));

	ret = cnic_submit_kwqe_16(dev, ISCSI_RAMROD_CMD_ID_UPDATE_CONN,
			req->context_id, ISCSI_CONNECTION_TYPE, &l5_data);
	return ret;
}
