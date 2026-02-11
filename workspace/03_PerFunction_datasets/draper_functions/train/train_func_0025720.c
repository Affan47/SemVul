inbound_thread_main(void *arg)
{
	while (stop == 0) {
		int rc;
		if (hup)
			nudge_queue();
		do {
			rc = poll(pfd, pfd_cnt, 20000);
		} while (rc < 0 && errno == EAGAIN && stop == 0);
		if (rc == 0)
			continue;


		if (rc > 0) {

			int i = 0;
			while (i < pfd_cnt) {
				if (pfd[i].revents & POLLIN)
					pfd_cb[i](pfd[i].fd);
				i++;
			}
		}
	}

	nudge_queue();
	return NULL;
}
