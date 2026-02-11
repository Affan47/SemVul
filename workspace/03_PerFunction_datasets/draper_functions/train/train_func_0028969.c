zhenhua_interrupt(struct serio *serio, unsigned char data, unsigned int flags)
{
	struct zhenhua *zhenhua = serio_get_drvdata(serio);


	if (data == 0xef)
		zhenhua->idx = 0;
	else if (zhenhua->idx == 0)
		return IRQ_HANDLED;

	if (zhenhua->idx < ZHENHUA_MAX_LENGTH)
		zhenhua->data[zhenhua->idx++] = bitrev8(data);

	if (zhenhua->idx == ZHENHUA_MAX_LENGTH) {
		zhenhua_process_packet(zhenhua);
		zhenhua->idx = 0;
	}

	return IRQ_HANDLED;
}
