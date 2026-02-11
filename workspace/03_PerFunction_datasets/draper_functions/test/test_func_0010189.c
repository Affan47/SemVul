snd_ensoniq_midi_input_open(struct snd_rawmidi_substream *substream)
{
	struct ensoniq *ensoniq = substream->rmidi->private_data;

	spin_lock_irq(&ensoniq->reg_lock);
	ensoniq->uartm |= ES_MODE_INPUT;
	ensoniq->midi_input = substream;
	if (!(ensoniq->uartm & ES_MODE_OUTPUT)) {
		outb(ES_CNTRL(3), ES_REG(ensoniq, UART_CONTROL));
		outb(ensoniq->uartc = 0, ES_REG(ensoniq, UART_CONTROL));
		outl(ensoniq->ctrl |= ES_UART_EN, ES_REG(ensoniq, CONTROL));
	}
	spin_unlock_irq(&ensoniq->reg_lock);
	return 0;
}
