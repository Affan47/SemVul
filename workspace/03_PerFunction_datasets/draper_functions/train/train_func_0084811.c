usb6fire_midi_in_received(
		struct midi_runtime *rt, u8 *data, int length)
{
	unsigned long flags;

	spin_lock_irqsave(&rt->in_lock, flags);
	if (rt->in)
		snd_rawmidi_receive(rt->in, data, length);
	spin_unlock_irqrestore(&rt->in_lock, flags);
}
