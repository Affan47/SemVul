sps_set_authUsername(bool success)
{
	QByteArray a(2);
	a[0] = 0x01;
	a[1] = success ? 0x00 : 0xff;
	return a;
}
