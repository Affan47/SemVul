ufshcd_complete_dev_init(struct ufs_hba *hba)
{
	int i, retries, err = 0;
	bool flag_res = 1;

	for (retries = QUERY_REQ_RETRIES; retries > 0; retries--) {

		err = ufshcd_query_flag(hba, UPIU_QUERY_OPCODE_SET_FLAG,
					QUERY_FLAG_IDN_FDEVICEINIT, NULL);
		if (!err || err == -ETIMEDOUT)
			break;
		dev_dbg(hba->dev, "%s: error %d retrying\n", __func__, err);
	}
	if (err) {
		dev_err(hba->dev,
			"%s setting fDeviceInit flag failed with error %d\n",
			__func__, err);
		goto out;
	}


	for (i = 0; i < 100 && !err && flag_res; i++) {
		for (retries = QUERY_REQ_RETRIES; retries > 0; retries--) {
			err = ufshcd_query_flag(hba,
					UPIU_QUERY_OPCODE_READ_FLAG,
					QUERY_FLAG_IDN_FDEVICEINIT, &flag_res);
			if (!err || err == -ETIMEDOUT)
				break;
			dev_dbg(hba->dev, "%s: error %d retrying\n", __func__,
					err);
		}
	}
	if (err)
		dev_err(hba->dev,
			"%s reading fDeviceInit flag failed with error %d\n",
			__func__, err);
	else if (flag_res)
		dev_err(hba->dev,
			"%s fDeviceInit was not cleared by the device\n",
			__func__);

out:
	return err;
}
