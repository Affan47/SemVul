xioctl(int nFd, int nRequest, void *pArg)
{
	int nRst;

	do {
		nRst = ioctl(nFd, nRequest, pArg);
	} while (-1 == nRst && EINTR == errno);

	return nRst;
}
