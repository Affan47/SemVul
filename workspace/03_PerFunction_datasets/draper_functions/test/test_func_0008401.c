growstackstr(void)
{
	size_t len = stackblocksize();
	if (herefd >= 0 && len >= 1024) {
		full_write(herefd, stackblock(), len);
		return stackblock();
	}
	growstackblock();
	return (char *)stackblock() + len;
}
