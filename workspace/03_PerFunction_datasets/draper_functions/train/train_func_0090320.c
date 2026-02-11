nbdclient_main(int argc, char **argv)
{
	unsigned long timeout = 0;
#if BB_MMU
	int nofork = 0;
#endif
	char *host, *port, *device;
	struct nbd_header_t {
		uint64_t magic1;
		uint64_t magic2;
		uint64_t devsize;
		uint32_t flags;
		char data[124];
	} nbd_header;
	struct bug_check {
		char c[offsetof(struct nbd_header_t, data) == 8+8+8+4 ? 1 : -1];
	};


	if (argc != 4)
		bb_show_usage();

#if !BB_MMU
	bb_daemonize_or_rexec(DAEMON_CLOSE_EXTRA_FDS, argv);
#endif

	host = argv[1];
	port = argv[2];
	device = argv[3];


	for (;;) {
		int sock, nbd;
		int ro;


		nbd = xopen(device, O_RDWR);


		sock = create_and_connect_stream_or_die(host, xatou16(port));
		setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &const_int_1, sizeof(const_int_1));


		xread(sock, &nbd_header, 8+8+8+4 + 124);
		if (memcmp(&nbd_header.magic1, "NBDMAGIC""\x00\x00\x42\x02\x81\x86\x12\x53", 16) != 0)
			bb_error_msg_and_die("login failed");


		ioctl(nbd, NBD_SET_BLKSIZE, 4096);
		ioctl(nbd, NBD_SET_SIZE_BLOCKS, SWAP_BE64(nbd_header.devsize) / 4096);
		ioctl(nbd, NBD_CLEAR_SOCK);


		ro = (nbd_header.flags & SWAP_BE32(2)) / SWAP_BE32(2);
		if (ioctl(nbd, BLKROSET, &ro) < 0)
			bb_perror_msg_and_die("BLKROSET");

		if (timeout)
			if (ioctl(nbd, NBD_SET_TIMEOUT, timeout))
				bb_perror_msg_and_die("NBD_SET_TIMEOUT");
		if (ioctl(nbd, NBD_SET_SOCK, sock))
			bb_perror_msg_and_die("NBD_SET_SOCK");


#if BB_MMU


		if (fork() == 0) {
			char *s = strrchr(device, '/');
			sprintf(nbd_header.data, "/sys/block/%.32s/pid", s ? s + 1 : device);

			for (;;) {
				int fd = open(nbd_header.data, O_RDONLY);
				if (fd >= 0) {

					break;
				}
				sleep(1);
			}
			open(device, O_RDONLY);
			return 0;
		}


		if (!nofork) {
			daemon(0, 0);
			nofork = 1;
		}
#endif


		if (ioctl(nbd, NBD_DO_IT) >= 0 || errno == EBADR) {

			ioctl(nbd, NBD_CLEAR_QUEUE);
			ioctl(nbd, NBD_CLEAR_SOCK);
			break;
		}

		close(sock);
		close(nbd);
	}

	return 0;
}
