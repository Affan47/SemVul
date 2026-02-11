meta_render_id3v2_rva2(meta_frame_t * frame, unsigned char ** buf, int * size) {

	unsigned char * data;
	int length;
	char * frame_id;
	int len1;
	signed int voladj_fixed;

	if (frame->field_val[0] == '\0') {
		free(frame->field_val);
		frame->field_val = strdup("Aqualung");
	}
	len1 = strlen(frame->field_val);
	length = 15 + len1;
	data = (unsigned char *)malloc(length);
	if (data == NULL) {
		fprintf(stderr, "meta_render_id3v2_apic: malloc error\n");
		return;
	}
	meta_get_fieldname_embedded(META_TAG_ID3v2, frame->type, &frame_id);
	memcpy(data, frame_id, 4);

	memcpy(data+10, frame->field_val, len1);
	data[10+len1] = '\0';
	data[11+len1] = 0x01;

	voladj_fixed = frame->float_val * 512;
	data[12+len1] = (voladj_fixed & 0xff00) >> 8;
	data[13+len1] = voladj_fixed & 0xff;
	data[14+len1] = 0x00;

	meta_render_append_frame(data, length, buf, size);
	free(data);
}
