message_integrity_check(const QByteArray &buf, int offset, const QByteArray &key)
{
	QByteArray mival = QByteArray::fromRawData(buf.data() + offset + 4, 20);
	QByteArray micalc = message_integrity_calc((const quint8 *)buf.data(), offset, key);
	if(mival == micalc)
		return true;
	else
		return false;
}
