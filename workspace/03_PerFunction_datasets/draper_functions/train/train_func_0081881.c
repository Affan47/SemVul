handle_body(void)
{
	int rc = 0;
	static char newline[2000];
	static char *np = newline;


	if (content_top->boundary) {
		if (!find_boundary())
			return;
	}

	do {

		if (content_top->boundary && is_multipart_boundary(line)) {

			if ((transfer_encoding == TE_BASE64)  &&
			    (np != newline)) {
				handle_filter(newline);
			}
			if (!handle_boundary())
				return;
		}


		decode_transfer_encoding(line);

		switch (transfer_encoding) {
		case TE_BASE64:
		{
			char *op = line;


			if (message_type != TYPE_TEXT) {
				rc = handle_filter(line);
				break;
			}


			do {
				while (*op != '\n' && *op != 0)
					*np++ = *op++;
				*np = *op;
				if (*np != 0) {

					*(++np) = 0;
					op++;
					rc = handle_filter(newline);
					np = newline;
				}
			} while (*op != 0);


			break;
		}
		default:
			rc = handle_filter(line);
		}
		if (rc)

			break;
	} while (fgets(line, sizeof(line), fin));

	return;
}
