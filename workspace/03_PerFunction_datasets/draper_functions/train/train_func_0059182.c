_get_boxes(char *buf, int max_len, int dims, int brackets)
{
	int len=0, i;
	int curr_min[dims], curr_max[dims];


	curr_min[0] = -1;


	while(_get_next_box(curr_min, curr_max, dims)) {


		if (!memcmp(curr_min, curr_max, dim_grid_size)) {
			for(i = 0; i<dims; i++) {
				if (len >= max_len)
					goto end_it;
				buf[len++] = alpha_num[curr_min[i]];
			}
			if (len >= max_len)
				goto end_it;
			buf[len++] = ',';
		} else {
			for(i = 0; i<dims; i++) {
				if (len >= max_len)
					goto end_it;
				buf[len++] = alpha_num[curr_min[i]];
			}
			if (len >= max_len)
				goto end_it;
			buf[len++] = 'x';
			for(i = 0; i<dims; i++) {
				if (len >= max_len)
					goto end_it;
				buf[len++] = alpha_num[curr_max[i]];
			}
			if (len >= max_len)
				goto end_it;
			buf[len++] = ',';
		}
	}

	if (brackets)
		buf[len - 1] = ']';
	else
		buf[len - 1] = '\0';
end_it:

	buf[len]   = '\0';

	return len;
}
