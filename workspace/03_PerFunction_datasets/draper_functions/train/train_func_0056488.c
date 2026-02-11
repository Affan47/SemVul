gsp_receive(struct garmin_data *garmin_data_p,
		       const unsigned char *buf, int count)
{
	struct device *dev = &garmin_data_p->port->dev;
	unsigned long flags;
	int offs = 0;
	int ack_or_nak_seen = 0;
	__u8 *dest;
	int size;

	int dleSeen;


	int skip;
	__u8 data;

	spin_lock_irqsave(&garmin_data_p->lock, flags);
	dest = garmin_data_p->inbuffer;
	size = garmin_data_p->insize;
	dleSeen = garmin_data_p->flags & FLAGS_GSP_DLESEEN;
	skip = garmin_data_p->flags & FLAGS_GSP_SKIP;
	spin_unlock_irqrestore(&garmin_data_p->lock, flags);


	if (size == 0)
		size = GSP_INITIAL_OFFSET;

	while (offs < count) {

		data = *(buf+offs);
		offs++;

		if (data == DLE) {
			if (skip) {
				skip = 0;
				size = GSP_INITIAL_OFFSET;
				dleSeen = 1;
			} else if (dleSeen) {
				dest[size++] = data;
				dleSeen = 0;
			} else {
				dleSeen = 1;
			}
		} else if (data == ETX) {
			if (dleSeen) {


				data = dest[GSP_INITIAL_OFFSET];

				if (data == ACK) {
					ack_or_nak_seen = ACK;
					dev_dbg(dev, "ACK packet complete.\n");
				} else if (data == NAK) {
					ack_or_nak_seen = NAK;
					dev_dbg(dev, "NAK packet complete.\n");
				} else {
					dev_dbg(dev, "packet complete - id=0x%X.\n",
						0xFF & data);
					gsp_rec_packet(garmin_data_p, size);
				}

				skip = 1;
				size = GSP_INITIAL_OFFSET;
				dleSeen = 0;
			} else {
				dest[size++] = data;
			}
		} else if (!skip) {

			if (dleSeen) {
				size = GSP_INITIAL_OFFSET;
				dleSeen = 0;
			}

			dest[size++] = data;
		}

		if (size >= GPS_IN_BUFSIZ) {
			dev_dbg(dev, "%s - packet too large.\n", __func__);
			skip = 1;
			size = GSP_INITIAL_OFFSET;
			dleSeen = 0;
		}
	}

	spin_lock_irqsave(&garmin_data_p->lock, flags);

	garmin_data_p->insize = size;


	if (skip)
		garmin_data_p->flags |= FLAGS_GSP_SKIP;
	else
		garmin_data_p->flags &= ~FLAGS_GSP_SKIP;

	if (dleSeen)
		garmin_data_p->flags |= FLAGS_GSP_DLESEEN;
	else
		garmin_data_p->flags &= ~FLAGS_GSP_DLESEEN;

	spin_unlock_irqrestore(&garmin_data_p->lock, flags);

	if (ack_or_nak_seen) {
		if (gsp_next_packet(garmin_data_p) > 0)
			garmin_data_p->state = STATE_ACTIVE;
		else
			garmin_data_p->state = STATE_GSP_WAIT_DATA;
	}
	return count;
}
