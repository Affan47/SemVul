snd_midi_event_decode(snd_midi_event_t *dev, unsigned char *buf, long count, const snd_seq_event_t *ev)
{
	int cmd;
	long qlen;
	unsigned int type;

	if (ev->type == SND_SEQ_EVENT_NONE)
		return -ENOENT;

	for (type = 0; type < numberof(status_event); type++) {
		if (ev->type == status_event[type].event)
			goto __found;
	}
	for (type = 0; type < numberof(extra_event); type++) {
		if (ev->type == extra_event[type].event)
			return extra_event[type].decode(dev, buf, count, ev);
	}
	return -ENOENT;

      __found:
	if (type >= ST_SPECIAL)
		cmd = 0xf0 + (type - ST_SPECIAL);
	else

		cmd = 0x80 | (type << 4) | (ev->data.note.channel & 0x0f);


	if (cmd == MIDI_CMD_COMMON_SYSEX) {
		snd_midi_event_reset_decode(dev);
		qlen = ev->data.ext.len;
		if (count < qlen)
			return -ENOMEM;
		switch (ev->flags & SND_SEQ_EVENT_LENGTH_MASK) {
		case SND_SEQ_EVENT_LENGTH_FIXED:
			return -EINVAL;
		}
		memcpy(buf, ev->data.ext.ptr, qlen);
		return qlen;
	} else {
		unsigned char xbuf[4];

		if ((cmd & 0xf0) == 0xf0 || dev->lastcmd != cmd || dev->nostat) {
			dev->lastcmd = cmd;
			xbuf[0] = cmd;
			if (status_event[type].decode)
				status_event[type].decode(ev, xbuf + 1);
			qlen = status_event[type].qlen + 1;
		} else {
			if (status_event[type].decode)
				status_event[type].decode(ev, xbuf + 0);
			qlen = status_event[type].qlen;
		}
		if (count < qlen)
			return -ENOMEM;
		memcpy(buf, xbuf, qlen);
		return qlen;
	}
}
