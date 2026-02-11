uidNum(mail::imap *i, size_t j)
{
	if (i->currentFolder == NULL || j >= i->currentFolder->index.size())
		return 0;


	string uid=i->currentFolder->index[j].uid;

	size_t n=uid.find('/');

	if (n == string::npos)
		return 0;

	uid=uid.substr(n+1);

	n=0;

	istringstream(uid.c_str()) >> n;

	return n;
}
