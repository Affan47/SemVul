gettag_set_info(h10db_t* h10db, int index, const media_info* info)
{
	static const ucs2_char_t ucs2_empty[1] = {0};

	if (h10db && info) {
		ucs2strip(info->title);
		if (info->title && ucs2icmp(info->title, ucs2cs_unknown_title) != 0) {
			h10db_set_title(h10db, index, info->title);
		} else {
			h10db_set_title(h10db, index, info->filename);
		}
		ucs2strip(info->artist);
		if (info->artist && ucs2icmp(info->artist, ucs2cs_unknown_artist) != 0) {
			h10db_set_artist(h10db, index, info->artist);
		} else {
			h10db_set_artist(h10db, index, ucs2_empty);
		}
		ucs2strip(info->album);
		if (info->album && ucs2icmp(info->album, ucs2cs_unknown_album) != 0) {
			h10db_set_album(h10db, index, info->album);
		} else {
			h10db_set_album(h10db, index, ucs2_empty);
		}
		ucs2strip(info->genre);
		if (info->genre && ucs2icmp(info->genre, ucs2cs_unknown_genre) != 0) {
			h10db_set_genre(h10db, index, info->genre);
		} else {
			h10db_set_genre(h10db, index, ucs2_empty);
		}
		h10db_set_tracknumber(h10db, index, info->tracknumer);
		h10db_set_year(h10db, index, info->year);
		h10db_set_filesize(h10db, index, info->filesize);
		h10db_set_duration(h10db, index, info->duration);
		h10db_set_samplerate(h10db, index, info->samplerate);
		h10db_set_bitrate(h10db, index, info->bitrate);
		h10db_set_unknown5(h10db, index, info->tracknumer);
		h10db_set_unknown6(h10db, index, ucs2_empty);
		h10db_set_unknown8(h10db, index, ucs2_empty);
	}

	return 0;
}
