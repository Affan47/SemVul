set_prga(struct wstate *ws, unsigned char* iv,
		     unsigned char* cipher, unsigned char* clear, int len)
{
	int i;
	int fd;

	if (ws->ws_pi.pi_len != 0)
		free(ws->ws_pi.pi_prga);

	ws->ws_pi.pi_prga = (unsigned char*) malloc(len);
	if (!ws->ws_pi.pi_prga) {
		perror("malloc()");
		exit(1);
	}

	ws->ws_pi.pi_len = len;
	memcpy(ws->ws_pi.pi_iv, iv, 3);

	for (i = 0; i < len; i++) {
		ws->ws_pi.pi_prga[i] =  ( cipher ? (clear[i] ^ cipher[i]) :
				 	        clear[i]);
	}

	time_print("Got %d bytes of prga IV=(%.02x:%.02x:%.02x) PRGA=",
	       ws->ws_pi.pi_len, ws->ws_pi.pi_iv[0], ws->ws_pi.pi_iv[1],
	       ws->ws_pi.pi_iv[2]);
	hexdump(ws->ws_pi.pi_prga, ws->ws_pi.pi_len);

	if (!cipher)
		return;

	fd = open(PRGA_FILE, O_WRONLY | O_CREAT,
		  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (fd == -1) {
		perror("open()");
		exit(1);
	}

	i = write(fd, ws->ws_pi.pi_iv, 3);
	if (i == -1) {
		perror("write()");
		exit(1);
	}
	if (i != 3) {
		printf("Wrote %d out of %d\n", i, 3);
		exit(1);
	}

	i = write(fd, ws->ws_pi.pi_prga, ws->ws_pi.pi_len);
	if (i == -1) {
		perror("write()");
		exit(1);
	}
	if (i != ws->ws_pi.pi_len) {
		printf("Wrote %d out of %d\n", i, ws->ws_pi.pi_len);
		exit(1);
	}

	close(fd);
}
