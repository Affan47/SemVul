parse_id3v20 (const gchar          *data,
              size_t                size,
              id3tag               *info,
              const gchar          *uri,
              TrackerSparqlBuilder *metadata,
              MP3Data              *filedata,
              size_t               *offset_delta)
{
	gint unsync;
	guint tsize;
	guint pos;

	if ((size < 16) ||
	    (data[0] != 0x49) ||
	    (data[1] != 0x44) ||
	    (data[2] != 0x33) ||
	    (data[3] != 0x02) ||
	    (data[4] != 0x00)) {
		return;
	}

	unsync = (data[5] & 0x80) > 0;
	tsize = (((data[6] & 0x7F) << 21) |
	         ((data[7] & 0x7F) << 14) |
	         ((data[8] & 0x7F) << 07) |
	         ((data[9] & 0x7F) << 00));

	if (tsize + 10 > size)  {
		return;
	}
	pos = 10;

	while (pos < size) {
		id3v2frame frame;
		size_t csize;

		if (pos + 6 > size)  {
			return;
		}

		frame = id3v2_get_frame (&data[pos]);

		csize = (((unsigned char)(data[pos + 3]) << 16) +
		         ((unsigned char)(data[pos + 4]) << 8) +
		         ((unsigned char)(data[pos + 5]) ) );

		pos += 6;

		if (frame == ID3V2_UNKNOWN) {

			pos += csize;
			continue;
		}

		if (pos + csize > size) {
			break;
		} else if (csize == 0) {
			continue;
		}


		if (unsync) {
			size_t  unsync_size;
			gchar  *body;

			un_unsync (&data[pos], csize, (unsigned char **) &body, &unsync_size);
			get_id3v20_tags (frame, body, unsync_size, info, uri, metadata, filedata);
			g_free (body);
		} else {
			get_id3v20_tags (frame, &data[pos], csize, info, uri, metadata, filedata);
		}

		pos += csize;
	}

	*offset_delta = tsize + 10;
}
