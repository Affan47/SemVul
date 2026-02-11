QRinput_setVersionAndErrorCorrectionLevel(QRinput *input, int version, QRecLevel level)
{
	if(input->mqr) {
		if(version <= 0 || version > MQRSPEC_VERSION_MAX) goto INVALID;
		if((MQRspec_getECCLength(version, level) == 0)) goto INVALID;
	} else {
		if(version < 0 || version > QRSPEC_VERSION_MAX) goto INVALID;
		if(level > QR_ECLEVEL_H) goto INVALID;
	}

	input->version = version;
	input->level = level;

	return 0;

INVALID:
	errno = EINVAL;
	return -1;
}
