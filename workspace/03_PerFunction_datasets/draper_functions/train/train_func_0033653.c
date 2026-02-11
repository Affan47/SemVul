read_flattened_format(int fd, off_t offset, void *buf, size_t size)
{
	unsigned long long	index, index_start, index_end;
	int64_t			range_start, range_end;
	size_t			read_size, remain_size;
	off_t			offset_read;
	struct flat_data	*ptr;

	index_start = 0;
	index_end   = afd.num_array;

	while (1) {
		index = (index_start + index_end) / 2;
		ptr = afd.array + index;
		range_start = ptr->off_rearranged;
		range_end   = ptr->off_rearranged + ptr->buf_size;

		if ((range_start <= offset) && (offset < range_end)) {

			offset_read = (offset - range_start) + ptr->off_flattened;

			if (offset + size <= range_end) {
				if (!read_raw_dump_file(fd, offset_read, buf, size))
					return FALSE;
				break;
			}


			read_size   = range_end - offset;
			remain_size = size - read_size;
			if (!read_raw_dump_file(fd, offset_read, buf, read_size))
				return FALSE;
			if (!read_flattened_format(fd, offset + read_size,
					(char *)buf + read_size, remain_size))
				return FALSE;
			break;

		} else if ((index == index_start) &&
			   (index_start + 1 == index_end)) {


			ptr = afd.array + index_end;
			if (offset + size <= ptr->off_rearranged) {
				memset(buf, 0x0, size);
			} else {
				read_size   = ptr->off_rearranged - offset;
				remain_size = size - read_size;
				memset(buf, 0x0, read_size);
				if (!read_flattened_format(fd,
						offset + read_size,
						(char *)buf + read_size,
						remain_size))
					return FALSE;
			}
			break;

		} else if (offset < ptr->off_rearranged)
			index_end   = index;
		else
			index_start = index;
	}
	return TRUE;
}
