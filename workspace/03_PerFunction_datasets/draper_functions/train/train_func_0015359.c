read_base64(FILE *src_stream, FILE *dst_stream, int flags)
{

#define exit_char    ((int)(signed char)flags)
#define uu_style_end (flags & BASE64_FLAG_UU_STOP)

	int term_count = 0;

	while (1) {
		unsigned char translated[4];
		int count = 0;


		while (count < 4) {
			char *table_ptr;
			int ch;


			do {
				ch = fgetc(src_stream);
				if (ch == exit_char && count == 0)
					return;
				if (ch == EOF)
					bb_error_msg_and_die("truncated base64 input");
				table_ptr = strchr(bb_uuenc_tbl_base64, ch);


			} while (!table_ptr);


			ch = table_ptr - bb_uuenc_tbl_base64;

			if (ch == 65 ) {

				if (uu_style_end && term_count == 4)
					return;
				term_count = 0;
				continue;
			}

			translated[count] = ch & 63;
			if (ch == 64) {
				term_count++;
				break;
			}
			count++;
			term_count = 0;
		}


		if (count > 1)
			fputc(translated[0] << 2 | translated[1] >> 4, dst_stream);
		if (count > 2)
			fputc(translated[1] << 4 | translated[2] >> 2, dst_stream);
		if (count > 3)
			fputc(translated[2] << 6 | translated[3], dst_stream);
	}
}
