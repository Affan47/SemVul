_picolcd_flash_write(struct picolcd_data *data, int report_id,
		const char __user *u, size_t s, loff_t *off)
{
	struct picolcd_pending *resp;
	u8 raw_data[36];
	ssize_t ret = 0;
	int len_off, err = -EIO;

	while (s > 0) {
		err = -EIO;
		len_off = _picolcd_flash_setaddr(data, raw_data, *off);
		raw_data[len_off] = s > 32 ? 32 : s;
		if (copy_from_user(raw_data+len_off+1, u, raw_data[len_off])) {
			err = -EFAULT;
			break;
		}
		resp = picolcd_send_and_wait(data->hdev, report_id, raw_data,
				len_off+1+raw_data[len_off]);
		if (!resp || !resp->in_report)
			goto skip;
		if (resp->in_report->id == REPORT_MEMORY ||
			resp->in_report->id == REPORT_BL_WRITE_MEMORY) {
			if (memcmp(raw_data, resp->raw_data, len_off+1+raw_data[len_off]) != 0)
				goto skip;
			*off += raw_data[len_off];
			s    -= raw_data[len_off];
			ret  += raw_data[len_off];
			err   = 0;
		}
skip:
		kfree(resp);
		if (err)
			break;
	}
	return ret > 0 ? ret : err;
}
