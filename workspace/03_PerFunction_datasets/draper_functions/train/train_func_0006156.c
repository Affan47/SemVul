cavan_fifo_write_raw(struct cavan_fifo *fifo, const char *buff, size_t size)
{
	size_t size_bak = size;

	while (size)
	{
		ssize_t wrlen;

		if (fifo->data_end < fifo->mem_end)
		{
			wrlen = fifo->mem_end - fifo->data_end;
		}
		else
		{
			if (fifo->write(fifo, fifo->mem, fifo->size) != (ssize_t) fifo->size)
			{
				return -EFAULT;
			}

			wrlen = fifo->size;
			fifo->data_end = fifo->mem;
		}

		if (fifo->data_end == fifo->mem)
		{
			while (size >= fifo->size)
			{
				if (fifo->write(fifo, buff, fifo->size) != (ssize_t) fifo->size)
				{
					return -EFAULT;
				}

				buff += fifo->size;
				size -= fifo->size;
			}
		}

		if (wrlen > (ssize_t) size)
		{
			wrlen = size;
		}

		mem_copy(fifo->data_end, buff, wrlen);
		fifo->data_end += wrlen;

		size -= wrlen;
		buff += wrlen;
	}

	return size_bak;
}
