meta_parse_id3v2_t___(metadata_t * meta, unsigned char * buf, int len) {

	char frame_id[5];
	int type;
	char * val;

	memcpy(frame_id, buf, 4);
	frame_id[4] = '\0';


	if ((strcmp(frame_id, "TDAT") == 0) ||
	    (strcmp(frame_id, "TIME") == 0) ||
	    (strcmp(frame_id, "TRDA") == 0) ||
	    (strcmp(frame_id, "TYER") == 0)) {
		strcpy(frame_id, "TDRC");
	} else if (strcmp(frame_id, "TORY") == 0) {
		strcpy(frame_id, "TDOR");
	}

	type = meta_frame_type_from_embedded_name(META_TAG_ID3v2, frame_id);
	val = meta_id3v2_to_utf8(buf[10], buf+11, len-1);
	if (val != NULL) {
		metadata_add_frame_from_keyval(meta, META_TAG_ID3v2, frame_id, val);
		g_free(val);
	}
}
