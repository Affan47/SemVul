newInternalBuffer(string const & s)
{
	Buffer * const buf = createNewBuffer(s, false);
	if (buf) {
		buf->setInternal(true);
		binternal.push_back(buf);
	}
	return buf;
}
