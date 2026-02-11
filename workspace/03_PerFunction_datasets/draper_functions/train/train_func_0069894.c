snd_rawmidi_virtual_read(snd_rawmidi_t *rmidi, void *buffer, size_t size)
{
	snd_rawmidi_virtual_t *virt = rmidi->private_data;
	ssize_t result = 0;
	int size1, err;

	while (size > 0) {
		if (! virt->in_buf_ofs) {
			err = snd_seq_event_input_pending(virt->handle, 1);
			if (err <= 0 && result > 0)
				return result;
			err = snd_seq_event_input(virt->handle, &virt->in_event);
			if (err < 0)
				return result > 0 ? result : err;

			if (virt->in_event->type == SND_SEQ_EVENT_SYSEX) {
				virt->in_buf_ptr = virt->in_event->data.ext.ptr;
				virt->in_buf_size = virt->in_event->data.ext.len;
			} else {
				virt->in_buf_ptr = virt->in_tmp_buf;
				virt->in_buf_size = snd_midi_event_decode(virt->midi_event,
									  (unsigned char *)virt->in_tmp_buf,
									  sizeof(virt->in_tmp_buf),
									  virt->in_event);
			}
			if (virt->in_buf_size <= 0)
				continue;
		}
		size1 = virt->in_buf_size - virt->in_buf_ofs;
		if ((size_t)size1 > size) {
			virt->in_buf_ofs += size1 - size;
			memcpy(buffer, virt->in_buf_ptr, size);
			result += size;
			break;
		}
		memcpy(buffer, virt->in_buf_ptr + virt->in_buf_ofs, size1);
		size -= size1;
		result += size1;
		buffer += size1;
		virt->in_buf_ofs = 0;
	}

	return result;
}
