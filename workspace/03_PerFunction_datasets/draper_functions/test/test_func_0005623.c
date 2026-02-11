goldfish_audio_write(struct file *fp, const char __user *buf,
				    size_t count, loff_t *pos)
{
	struct goldfish_audio *data = fp->private_data;
	unsigned long irq_flags;
	ssize_t result = 0;
	char *kbuf;

	while (count > 0) {
		ssize_t copy = count;

		if (copy > WRITE_BUFFER_SIZE)
			copy = WRITE_BUFFER_SIZE;
		wait_event_interruptible(data->wait, data->buffer_status &
					(AUDIO_INT_WRITE_BUFFER_1_EMPTY |
					AUDIO_INT_WRITE_BUFFER_2_EMPTY));

		if ((data->buffer_status & AUDIO_INT_WRITE_BUFFER_1_EMPTY) != 0)
			kbuf = data->write_buffer1;
		else
			kbuf = data->write_buffer2;


		if (copy_from_user(kbuf, buf, copy)) {
			result = -EFAULT;
			break;
		}

		spin_lock_irqsave(&data->lock, irq_flags);


		if (kbuf == data->write_buffer1) {
			data->buffer_status &= ~AUDIO_INT_WRITE_BUFFER_1_EMPTY;
			AUDIO_WRITE(data, AUDIO_WRITE_BUFFER_1, copy);
		} else {
			data->buffer_status &= ~AUDIO_INT_WRITE_BUFFER_2_EMPTY;
			AUDIO_WRITE(data, AUDIO_WRITE_BUFFER_2, copy);
		}
		spin_unlock_irqrestore(&data->lock, irq_flags);

		buf += copy;
		result += copy;
		count -= copy;
	}
	return result;
}
