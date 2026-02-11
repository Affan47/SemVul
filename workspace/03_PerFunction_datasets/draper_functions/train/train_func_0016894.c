sp2_ci_poll_slot_status(struct dvb_ca_en50221 *en50221,
				int slot, int open)
{
	struct sp2 *s = en50221->data;
	u8 buf[2];
	int ret;

	dev_dbg(&s->client->dev, "slot:%d open:%d\n", slot, open);


	if (time_after(jiffies, s->next_status_checked_time)) {
		ret = sp2_read_i2c(s, 0x00, buf, 1);
		s->next_status_checked_time = jiffies +	msecs_to_jiffies(1000);

		if (ret)
			return 0;

		if (buf[0] & SP2_MOD_CTL_DET)
			s->status = DVB_CA_EN50221_POLL_CAM_PRESENT |
					DVB_CA_EN50221_POLL_CAM_READY;
		else
			s->status = 0;
	}

	return s->status;
}
