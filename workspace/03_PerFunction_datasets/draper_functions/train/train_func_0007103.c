QRraw_new(QRinput *input)
{
	QRRawCode *raw;
	int spec[5], ret;

	raw = (QRRawCode *)malloc(sizeof(QRRawCode));
	if(raw == NULL) return NULL;

	raw->datacode = QRinput_getByteStream(input);
	if(raw->datacode == NULL) {
		free(raw);
		return NULL;
	}

	QRspec_getEccSpec(input->version, input->level, spec);

	raw->version = input->version;
	raw->b1 = QRspec_rsBlockNum1(spec);
	raw->dataLength = QRspec_rsDataLength(spec);
	raw->eccLength = QRspec_rsEccLength(spec);
	raw->ecccode = (unsigned char *)malloc(raw->eccLength);
	if(raw->ecccode == NULL) {
		free(raw->datacode);
		free(raw);
		return NULL;
	}

	raw->blocks = QRspec_rsBlockNum(spec);
	raw->rsblock = (RSblock *)calloc(sizeof(RSblock), raw->blocks);
	if(raw->rsblock == NULL) {
		QRraw_free(raw);
		return NULL;
	}
	ret = RSblock_init(raw->rsblock, spec, raw->datacode, raw->ecccode);
	if(ret < 0) {
		QRraw_free(raw);
		return NULL;
	}

	raw->count = 0;

	return raw;
}
