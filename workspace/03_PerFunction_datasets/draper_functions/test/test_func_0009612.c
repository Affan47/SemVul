sms_deserialize(const unsigned char *buf,
		struct sms *sms, int len)
{
	if (len < 1)
		return FALSE;

	return sms_decode(buf + 1, len - 1, FALSE, buf[0], sms);
}
