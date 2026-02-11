namco_voice_select( int offset, int data, int ch ) {

	logerror("Voice %d mode: %d select: %02x\n", ch, rt_decode_mode, data );

	if ( data == 0 )
		sample_stop( ch );

	if (rt_decode_mode != 0) {
		switch ( data & 0xe0 ) {
			case 0x00:
			break;

			case 0x20:
				data &= 0x1f;
				data += rt_totalsamples[0];
			break;

			case 0x40:
				data &= 0x1f;
				data += rt_totalsamples[0] + rt_totalsamples[1];
			break;

			case 0x60:
				data &= 0x1f;
				data += rt_totalsamples[0] + rt_totalsamples[1] + rt_totalsamples[2];
			break;

			case 0x80:
				data &= 0x1f;
				data += rt_totalsamples[0] + rt_totalsamples[1] + rt_totalsamples[2] + rt_totalsamples[3];
			break;

			case 0xa0:
				data &= 0x1f;
				data += rt_totalsamples[0] + rt_totalsamples[1] + rt_totalsamples[2] + rt_totalsamples[3] + rt_totalsamples[4];
			break;

			case 0xc0:
				data &= 0x1f;
				data += rt_totalsamples[0] + rt_totalsamples[1] + rt_totalsamples[2] + rt_totalsamples[3] + rt_totalsamples[4] + rt_totalsamples[5];
			break;

			case 0xe0:
				data &= 0x1f;
				data += rt_totalsamples[0] + rt_totalsamples[1] + rt_totalsamples[2] + rt_totalsamples[3] + rt_totalsamples[4] + rt_totalsamples[5] + rt_totalsamples[6];
			break;
		}
	} else {
		switch ( data & 0xc0 ) {
			case 0x00:
			break;

			case 0x40:
				data &= 0x3f;
				data += rt_totalsamples[0];
			break;

			case 0x80:
				data &= 0x3f;
				data += rt_totalsamples[0] + rt_totalsamples[1];
			break;

			case 0xc0:
				data &= 0x3f;
				data += rt_totalsamples[0] + rt_totalsamples[1] + rt_totalsamples[2];
			break;
		}
	}

	voice[ch] = data - 1;
}
