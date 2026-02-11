spc_get_authUsername(QByteArray *from, SPCS_AUTHUSERNAME *s)
{
	if(from->size() < 1)
		return 0;
	unsigned char ver = from->at(0);
	if(ver != 0x01)
		return -1;
	if(from->size() < 2)
		return 0;
	unsigned char ulen = from->at(1);
	if((int)from->size() < ulen + 3)
		return 0;
	unsigned char plen = from->at(ulen+2);
	if((int)from->size() < ulen + plen + 3)
		return 0;
	QByteArray a = ByteStream::takeArray(from, ulen + plen + 3);

	QByteArray user, pass;
	user.resize(ulen+1);
	pass.resize(plen+1);
	memcpy(user.data(), a.data()+2, ulen);
	memcpy(pass.data(), a.data()+ulen+3, plen);
	s->user = QString::fromUtf8(user);
	s->pass = QString::fromUtf8(pass);
	return 1;
}
