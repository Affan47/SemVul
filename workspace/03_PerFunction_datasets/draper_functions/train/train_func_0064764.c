gdip_read_bmp_data (void *pointer, BYTE *data, int size, ImageSource source)
{
	switch (source) {
	case File:
		return fread (data, 1, size, (FILE*) pointer);
	case DStream: {


		int got;
		int total;
		dstream_t *loader;

		loader = (dstream_t *) pointer;
		total = 0;

		do {
			got = dstream_read (loader, data + total, size - total, 0);
			if (got < 1) {
				return total;
			}
			total += got;
		} while (total < size);

		return total;
	}
	case Memory: {
		MemorySource *ms = (MemorySource*)pointer;
		int len = (ms->pos + size < ms->size) ? size : ms->size - ms->pos;
		if (len > 0) {
			memcpy (data, ms->ptr + ms->pos, len);
			ms->pos += len;
		}
		return size;
	}
	default:
		return -1;
	}
}
