QRinput_encodeMode8(QRinput_List *entry, BitStream *bstream, int version, int mqr)
{
	int ret;

	if(mqr) {
		if(version < 3) {
			errno = EINVAL;
			return -1;
		}
		ret = BitStream_appendNum(bstream, version - 1, MQRSPEC_MODEID_8);
		if(ret < 0) return -1;
		ret = BitStream_appendNum(bstream, MQRspec_lengthIndicator(QR_MODE_8, version), entry->size);
		if(ret < 0) return -1;
	} else {
		ret = BitStream_appendNum(bstream, 4, QRSPEC_MODEID_8);
		if(ret < 0) return -1;
		ret = BitStream_appendNum(bstream, QRspec_lengthIndicator(QR_MODE_8, version), entry->size);
		if(ret < 0) return -1;
	}

	ret = BitStream_appendBytes(bstream, entry->size, entry->data);
	if(ret < 0) return -1;

	return 0;
}
