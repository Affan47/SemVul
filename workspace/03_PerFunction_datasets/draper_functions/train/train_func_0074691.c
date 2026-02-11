e2_copy_image_data(Epson_Scanner * s, SANE_Byte * data, SANE_Int max_length,
		   SANE_Int * length)
{
	if (!s->block && s->params.format == SANE_FRAME_RGB) {

		max_length /= 3;

		if (max_length > s->end - s->ptr)
			max_length = s->end - s->ptr;

		*length = 3 * max_length;

		while (max_length-- != 0) {
			*data++ = s->ptr[0];
			*data++ = s->ptr[s->params.pixels_per_line];
			*data++ = s->ptr[2 * s->params.pixels_per_line];
			++s->ptr;
		}

	} else {
		if (max_length > s->end - s->ptr)
			max_length = s->end - s->ptr;

		*length = max_length;

		if (s->params.depth == 1) {
			while (max_length-- != 0)
				*data++ = ~*s->ptr++;
		} else {
			memcpy(data, s->ptr, max_length);
			s->ptr += max_length;
		}
	}
}
