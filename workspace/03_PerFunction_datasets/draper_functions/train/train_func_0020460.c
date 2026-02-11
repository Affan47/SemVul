QRcode_encodeMask(QRinput *input, int mask)
{
	int width, version;
	QRRawCode *raw;
	unsigned char *frame, *masked, *p, code, bit;
	FrameFiller *filler;
	int i, j;
	QRcode *qrcode;

	if(input->version < 0 || input->version > QRSPEC_VERSION_MAX) {
		errno = EINVAL;
		return NULL;
	}
	if(input->level > QR_ECLEVEL_H) {
		errno = EINVAL;
		return NULL;
	}

	raw = QRraw_new(input);
	if(raw == NULL) return NULL;

	version = raw->version;
	width = QRspec_getWidth(version);
	frame = QRspec_newFrame(version);
	if(frame == NULL) {
		QRraw_free(raw);
		return NULL;
	}
	filler = FrameFiller_new(width, frame);
	if(filler == NULL) {
		QRraw_free(raw);
		free(frame);
		return NULL;
	}


	for(i=0; i<raw->dataLength + raw->eccLength; i++) {
		code = QRraw_getCode(raw);
		bit = 0x80;
		for(j=0; j<8; j++) {
			p = FrameFiller_next(filler);
			*p = 0x02 | ((bit & code) != 0);
			bit = bit >> 1;
		}
	}
	QRraw_free(raw);

	j = QRspec_getRemainder(version);
	for(i=0; i<j; i++) {
		p = FrameFiller_next(filler);
		*p = 0x02;
	}
	free(filler);

	if(mask < 0) {
		masked = Mask_mask(width, frame, input->level);
	} else {
		masked = Mask_makeMask(width, frame, mask, input->level);
	}
	if(masked == NULL) {
		free(frame);
		return NULL;
	}
	qrcode = QRcode_new(version, width, masked);

	free(frame);

	return qrcode;
}
