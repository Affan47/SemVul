get_ogg_serial_no_for_stream(char *fileName, u32 stream_num, Bool is_video)
{
	ogg_sync_state oy;
	u32 track, serial_no;
	ogg_page oggpage;
	ogg_packet oggpacket;
	ogg_stream_state os;
	FILE *f_in;


	if (!stream_num) return 0;

	f_in = gf_f64_open(fileName, "rb");
	if (!f_in) return 0;

	track = 0;
	serial_no = 0;
	ogg_sync_init(&oy);
	while (1) {
		if (!OGG_ReadPage(f_in, &oy, &oggpage)) break;
		if (!ogg_page_bos(&oggpage)) break;
		track ++;
		if (track != stream_num) continue;

		serial_no = ogg_page_serialno(&oggpage);
		ogg_stream_init(&os, serial_no);
		ogg_stream_pagein(&os, &oggpage);
		ogg_stream_packetpeek(&os, &oggpacket);

		if (is_video && (oggpacket.bytes >= 7) && !strncmp((char *)&oggpacket.packet[1], "theora", 6)) {
			ogg_stream_clear(&os);
			break;
		}
		if (!is_video && (oggpacket.bytes >= 7) && !strncmp((char *)&oggpacket.packet[1], "vorbis", 6)) {
			ogg_stream_clear(&os);
			break;
		}
		ogg_stream_clear(&os);
		serial_no = 0;
	}
	ogg_sync_clear(&oy);
	fclose(f_in);
	return serial_no;
}
