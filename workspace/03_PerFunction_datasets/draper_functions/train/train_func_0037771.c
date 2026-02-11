emsa3Encode(const QString &hashName, const QByteArray &digest, int size)
{
	QByteArray hash_id = get_hash_id(hashName);
	if(hash_id.isEmpty())
		return QByteArray();


	int basesize = hash_id.size() + digest.size() + 2;
	if(size == -1)
		size = basesize + 1;
	int padlen = size - basesize;
	if(padlen < 1)
		return QByteArray();

	QByteArray out(size, (char)0xff);
	out[0] = 0x01;
	out[padlen + 1] = 0x00;
	int at = padlen + 2;
	memcpy(out.data() + at, hash_id.data(), hash_id.size());
	at += hash_id.size();
	memcpy(out.data() + at, digest.data(), digest.size());
	return out;
}
