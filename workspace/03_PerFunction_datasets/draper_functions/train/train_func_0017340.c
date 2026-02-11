split_str(const char *src, int max_pixel_w, SCP_vector<int> &n_chars, SCP_vector<const char*> &p_str, char ignore_char)
{
	char buffer[SPLIT_STR_BUFFER_SIZE];
	const char *breakpoint = NULL;
	int sw, new_line = 1, line_num = 0, last_was_white = 0;
	int ignore_until_whitespace = 0, buf_index = 0;


	Assert(src != NULL);
	Assert(max_pixel_w > 0);

	memset(buffer, 0, SPLIT_STR_BUFFER_SIZE);


	while (is_white_space(*src))
		src++;

	p_str.clear();


	for (; *src; src++) {


		if (new_line) {
			if (is_gray_space(*src))
				continue;

			p_str.push_back(src);
			breakpoint = NULL;
			new_line = 0;
		}


		if (ignore_until_whitespace) {
			if ( is_white_space(*src) ) {
				ignore_until_whitespace = 0;


				if (*src == EOLN)
					src--;
			}

			continue;
		}


		if (*src == '\n') {
			n_chars.push_back(src - p_str.at(line_num));
			line_num++;
			new_line = 1;

			memset(buffer, 0, SPLIT_STR_BUFFER_SIZE);
			buf_index = 0;
			continue;
		}

		if (*src == ignore_char) {
			ignore_until_whitespace = 1;
			continue;
		}

		if (is_gray_space(*src)) {
			if (!last_was_white)
				breakpoint = src;

			last_was_white = 1;

		} else {

			last_was_white = 0;
		}


		buffer[buf_index] = *src;
		buf_index++;
		buffer[buf_index] = 0;

		gr_get_string_size(&sw, NULL, buffer);
		if (sw >= max_pixel_w) {
			const char *end;

			if (breakpoint) {
				end = src = breakpoint;

			} else {
				end = src;
				src--;
			}

			n_chars.push_back(end - p_str.at(line_num));
			Assert(n_chars.at(line_num));
			line_num++;
			new_line = 1;

			memset(buffer, 0, SPLIT_STR_BUFFER_SIZE);
			buf_index = 0;
			continue;
		}
	}

	if (!new_line && p_str.at(line_num)) {
		n_chars.push_back(src - p_str.at(line_num));
		Assert(n_chars.at(line_num));
		line_num++;
	}

	return line_num;
}
