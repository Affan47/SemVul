cavan_vfat_copy_name(char *dest, char *head, const u16 *src, size_t count)
{
	const u16 *last;

	for (last = src + count - 1; last >= src && dest >= head; dest--, last--)
	{
#if 1
		u16 value = *last;

		if (value & 0xFF00)
		{
			*dest = value >> 8;
			if (--dest < head)
			{
				break;
			}
		}

		*dest = value;
#else
		*dest = *last;
#endif
	}

	return dest;
}
