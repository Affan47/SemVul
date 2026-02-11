fb64_start(struct fb *fbp, int dir, int server)
{
	int x;
	unsigned char *p;
	int state;

	switch (dir) {
	case DIR_DECRYPT:


		state = fbp->state[dir-1];
		if (state == FAILED)
			state = IN_PROGRESS;
		break;

	case DIR_ENCRYPT:
		state = fbp->state[dir-1];
		if (state == FAILED)
			state = IN_PROGRESS;
		else if ((state & NO_SEND_IV) == 0) {
			break;
		}

		if (!VALIDKEY(fbp->krbdes_key)) {
		        fbp->need_start = 1;
			break;
		}

		state &= ~NO_SEND_IV;
		state |= NO_RECV_IV;
		if (encrypt_debug_mode)
			printf("Creating new feed\r\n");


		do {
		    if (RAND_bytes(fbp->temp_feed,
				   sizeof(*fbp->temp_feed)) != 1)
			abort();
		    DES_set_odd_parity(&fbp->temp_feed);
		} while(DES_is_weak_key(&fbp->temp_feed));

		p = fbp->fb_feed + 3;
		*p++ = ENCRYPT_IS;
		p++;
		*p++ = FB64_IV;
		for (x = 0; x < sizeof(DES_cblock); ++x) {
			if ((*p++ = fbp->temp_feed[x]) == IAC)
				*p++ = IAC;
		}
		*p++ = IAC;
		*p++ = SE;
		printsub('>', &fbp->fb_feed[2], p - &fbp->fb_feed[2]);
		telnet_net_write(fbp->fb_feed, p - fbp->fb_feed);
		break;
	default:
		return(FAILED);
	}
	return(fbp->state[dir-1] = state);
}
