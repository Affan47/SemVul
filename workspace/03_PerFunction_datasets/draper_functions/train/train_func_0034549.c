operator=(Buffer &buf)
{

    if (buf.size() != _nbytes) {
	resize(buf.size());
    }
    copy(buf.reference(), buf.size());

    return *this;
}
