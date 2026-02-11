parse_numeric_entity(const struct array entity)
{
	size_t i = 0;

	if (i < entity.size && '#' == entity.data[i]) {
		unsigned base;
		uint32 v;

		i++;
		switch (entity.data[i]) {
		case 'x':
		case 'X':
			base = 16;
			i++;
			break;
		default:
			base = 10;
		}
		v = 0;
		while (i < entity.size) {
			unsigned d;

			d = hex2int_inline(entity.data[i++]);
			if (d >= base)
				goto error;

			v = v * base + d;
			if (v >= 0x10ffffU)
				goto error;
		}
		if (0 == utf8_encoded_len(v))
			goto error;
		return v;
	}

error:
	return -1;
}
