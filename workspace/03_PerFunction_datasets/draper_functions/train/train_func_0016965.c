mmc_get_configuration(int host_no, struct scsi_cmd *cmd)
{
	struct mmc_info *mmc = dtype_priv(cmd->dev);
	char *data;
	char buf[1024];
	int rt, start;
	struct feature_descriptor *f;
	int tmp;

	rt = cmd->scb[1] & 0x03;

	start = cmd->scb[2];
	start = (start << 8) | cmd->scb[3];

	memset(buf, 0, sizeof(buf));
	data = buf;

	data += 4;


	*data++ = 0;
	*data++ = 0;

	*data++ = (mmc->current_profile >> 8) & 0xff;
	*data++ = mmc->current_profile & 0xff;


	for (f = features; f->func; f++) {

		if (f->feature < start)
			continue;

		if (rt == 2 && f->feature != start)
			continue;

		data = f->func(cmd, data, rt == 1);
	}

	tmp = data-buf;
	tmp -= 4;

	buf[0] = (tmp >> 24) & 0xff;
	buf[1] = (tmp >> 16) & 0xff;
	buf[2] = (tmp >> 8) & 0xff;
	buf[3] = tmp & 0xff;

	tmp = data-buf;

	memcpy(scsi_get_in_buffer(cmd), buf,
	       min_t(uint32_t, scsi_get_in_length(cmd), sizeof(buf)));


	return SAM_STAT_GOOD;
}
