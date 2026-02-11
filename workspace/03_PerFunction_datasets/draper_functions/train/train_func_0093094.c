snd_uart16550_output_write(struct snd_rawmidi_substream *substream)
{
	unsigned long flags;
	unsigned char midi_byte, addr_byte;
	struct snd_uart16550 *uart = substream->rmidi->private_data;
	char first;
	static unsigned long lasttime = 0;


	spin_lock_irqsave(&uart->open_lock, flags);

	if (uart->irq < 0)
		snd_uart16550_io_loop(uart);

	if (uart->adaptor == SNDRV_SERIAL_MS124W_MB) {
		while (1) {


			if (uart->buff_in_count > TX_BUFF_SIZE - 2)
				break;
			if (snd_rawmidi_transmit(substream, &midi_byte, 1) != 1)
				break;
#ifdef SNDRV_SERIAL_MS124W_MB_NOCOMBO

			addr_byte = (1 << (substream->number + 4)) | 0x08;
#else

			addr_byte = (substream->number << 4) | 0x08;

			if (addr_byte == 0x08)
				addr_byte = 0xf8;
#endif
			snd_uart16550_output_byte(uart, substream, addr_byte);

			snd_uart16550_output_byte(uart, substream, midi_byte);
		}
	} else {
		first = 0;
		while (snd_rawmidi_transmit_peek(substream, &midi_byte, 1) == 1) {


			if (first == 0 &&
			    (uart->adaptor == SNDRV_SERIAL_SOUNDCANVAS ||
			     uart->adaptor == SNDRV_SERIAL_GENERIC) &&
			    (uart->prev_out != substream->number ||
			     time_after(jiffies, lasttime + 3*HZ))) {

				if (snd_uart16550_buffer_can_write(uart, 3)) {


					uart->prev_out = substream->number;

					snd_uart16550_output_byte(uart, substream,
								  0xf5);

					snd_uart16550_output_byte(uart, substream,
								  uart->prev_out + 1);


					if (midi_byte < 0x80 &&
					    uart->adaptor == SNDRV_SERIAL_SOUNDCANVAS)
						snd_uart16550_output_byte(uart, substream, uart->prev_status[uart->prev_out]);
				} else if (!uart->drop_on_full)
					break;

			}


			if (!snd_uart16550_output_byte(uart, substream, midi_byte) &&
			    !uart->drop_on_full )
				break;

			if (midi_byte >= 0x80 && midi_byte < 0xf0)
				uart->prev_status[uart->prev_out] = midi_byte;
			first = 1;

			snd_rawmidi_transmit_ack( substream, 1 );
		}
		lasttime = jiffies;
	}
	spin_unlock_irqrestore(&uart->open_lock, flags);
}
