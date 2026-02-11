waitforhostname(int fd, const char *name, const char *port)
{


    struct addrinfo *res, *ai;
    struct addrinfo hints;
    nbgai_hdr_t hdr;
#define NIOV 1+2*16
    struct iovec iov[NIOV];
    int niov;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    hdr.err = getaddrinfo(name, port, &hints, &res);

    if (!hdr.err) {
	hdr.size = 0;
	iov[0].iov_base = (char*)&hdr;
	iov[0].iov_len = sizeof(hdr);
	niov = 1;
	for (ai = res; ai && niov < NIOV; ai = ai->ai_next) {
	    hdr.size += sizeof(*ai) + ai->ai_addrlen;
	    iov[niov].iov_base = (char*)ai;
	    iov[niov].iov_len = sizeof(*ai);
	    niov++;
	    iov[niov].iov_base = (char*)ai->ai_addr;
	    iov[niov].iov_len = ai->ai_addrlen;
	    niov++;
	}
	writev(fd, iov, niov);
	if (res) freeaddrinfo(res);
    } else {
	hdr.size = 0;
	write(fd, &hdr, sizeof(hdr));
    }
    close(fd);
}
