snd_emu10k1_midi_cmd(struct snd_emu10k1 * emu, struct snd_emu10k1_midi *midi, unsigned char cmd, int ack)
{
	unsigned long flags;
	int timeout, ok;

	spin_lock_irqsave(&midi->input_lock, flags);
	mpu401_write_data(emu, midi, 0x00);


	mpu401_write_cmd(emu, midi, cmd);
	if (ack) {
		ok = 0;
		timeout = 10000;
		while (!ok && timeout-- > 0) {
			if (mpu401_input_avail(emu, midi)) {
				if (mpu401_read_data(emu, midi) == MPU401_ACK)
					ok = 1;
			}
		}
		if (!ok && mpu401_read_data(emu, midi) == MPU401_ACK)
			ok = 1;
	} else {
		ok = 1;
	}
	spin_unlock_irqrestore(&midi->input_lock, flags);
	if (!ok) {
		dev_err(emu->card->dev,
			"midi_cmd: 0x%x failed at 0x%lx (status = 0x%x, data = 0x%x)!!!\n",
			   cmd, emu->port,
			   mpu401_read_stat(emu, midi),
			   mpu401_read_data(emu, midi));
		return 1;
	}
	return 0;
}
