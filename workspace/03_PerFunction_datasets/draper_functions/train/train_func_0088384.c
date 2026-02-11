extract_gif(f_state *s, u_int64_t c_offset, unsigned char *foundat, u_int64_t buflen,
						   s_spec *needle, u_int64_t f_offset)
{
	unsigned char	*buf = foundat;
	unsigned char	*currentpos = foundat;
	unsigned char	*extractbuf = NULL;
	int				bytes_to_search = 0;
	unsigned short	width = 0;
	unsigned short	height = 0;
	u_int64_t		file_size = 0;
	char			comment[32];
	foundat += 4;


	if (strncmp((char *)foundat, "9a", 2) == 0 || strncmp((char *)foundat, "7a", 2) == 0)
		{
		foundat += 2;
		width = htos(foundat, FOREMOST_LITTLE_ENDIAN);
		height = htos(&foundat[2], FOREMOST_LITTLE_ENDIAN);

		sprintf(comment, " (%d x %d)", width, height);
		strcat(needle->comment, comment);

		currentpos = foundat;
		if (buflen - (foundat - buf) >= needle->max_len)
			bytes_to_search = needle->max_len;
		else
			bytes_to_search = buflen - (foundat - buf);
		foundat = bm_search(needle->footer,
							needle->footer_len,
							foundat,
							bytes_to_search,
							needle->footer_bm_table,
							needle->case_sen,
							SEARCHTYPE_FORWARD);
		if (foundat)
		{


#ifdef DEBUG
			printx(foundat, 0, 16);
#endif
			file_size = (foundat - buf) + needle->footer_len;
#ifdef DEBUG
			printf("The GIF file size is  %llu  c_offset:=%llu\n", file_size, c_offset);
#endif
			extractbuf = buf;
			write_to_disk(s, needle, file_size, extractbuf, c_offset + f_offset);
			foundat += needle->footer_len;
			return foundat;
		}

		return NULL;

		}
	else
		{
		return foundat;
		}

}
