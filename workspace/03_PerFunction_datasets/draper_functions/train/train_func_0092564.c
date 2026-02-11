handle_body(void)
{
	struct strbuf prev = STRBUF_INIT;


	if (*content_top) {
		if (!find_boundary())
			goto handle_body_out;
	}

	do {

		if (*content_top && is_multipart_boundary(&line)) {

			if (prev.len) {
				handle_filter(&prev);
				strbuf_reset(&prev);
			}
			if (!handle_boundary())
				goto handle_body_out;
		}


		decode_transfer_encoding(&line);

		switch (transfer_encoding) {
		case TE_BASE64:
		case TE_QP:
		{
			struct strbuf **lines, **it, *sb;


			strbuf_insert(&line, 0, prev.buf, prev.len);
			strbuf_reset(&prev);


			if (message_type != TYPE_TEXT) {
				handle_filter(&line);
				break;
			}


			lines = strbuf_split(&line, '\n');
			for (it = lines; (sb = *it); it++) {
				if (*(it + 1) == NULL)
					if (sb->buf[sb->len - 1] != '\n') {

						strbuf_addbuf(&prev, sb);
						break;
					}
				handle_filter(sb);
			}


			strbuf_list_free(lines);
			break;
		}
		default:
			handle_filter(&line);
		}

	} while (!strbuf_getwholeline(&line, fin, '\n'));

handle_body_out:
	strbuf_release(&prev);
}
