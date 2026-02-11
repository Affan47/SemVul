snd_mpu401_uart_input_read(struct snd_mpu401 * mpu)
{
	int max = 128;
	unsigned char byte;

	while (max-- > 0) {
		if (! snd_mpu401_input_avail(mpu))
			break;
		byte = mpu->read(mpu, MPU401D(mpu));
		if (test_bit(MPU401_MODE_BIT_INPUT_TRIGGER, &mpu->mode))
			snd_rawmidi_receive(mpu->substream_input, &byte, 1);
	}
}
