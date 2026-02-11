check_loop_mode(int argc, char* argv[], int force) {
	int i;
	int loop_mode = 0, loop_sleep = 2000, loop_max = 0;

	if (force) {
		loop_mode = 1;
	}
	for (i=1; i < argc; i++) {
		char *p = argv[i];
		if (strstr(p, "--") == p) {
			p++;
		}
		if (strstr(p, "-loop") == p) {
			char *q;
			loop_mode = 1;
			if ((q = strchr(p, ',')) != NULL) {
				loop_max = atoi(q+1);
				*q = '\0';
			}
			if (strstr(p, "-loopbg") == p) {
				set_env("X11VNC_LOOP_MODE_BG", "1");
				loop_sleep = 500;
			}

			q = strpbrk(p, "0123456789");
			if (q) {
				loop_sleep = atoi(q);
				if (loop_sleep <= 0) {
					loop_sleep = 20;
				}
			}
		}
	}
	if (loop_mode && getenv("X11VNC_LOOP_MODE") == NULL) {
#if LIBVNCSERVER_HAVE_FORK
		char **argv2;
		int k, i = 1;

		set_env("X11VNC_LOOP_MODE", "1");
		argv2 = (char **) malloc((argc+1)*sizeof(char *));

		for (k=0; k < argc+1; k++) {
			argv2[k] = NULL;
			if (k < argc) {
				argv2[k] = argv[k];
			}
		}
		while (1) {
			int status;
			pid_t p;
			fprintf(stderr, "\n --- x11vnc loop: %d ---\n\n", i++);
			fflush(stderr);
			usleep(500 * 1000);
			if ((p = fork()) > 0)  {
				fprintf(stderr, " --- x11vnc loop: waiting "
				    "for: %d\n\n", p);
				wait(&status);
			} else if (p == -1) {
				fprintf(stderr, "could not fork\n");
				perror("fork");
				exit(1);
			} else {

				execvp(argv[0], argv2);
				exit(1);
			}

			if (loop_max > 0 && i > loop_max) {
				fprintf(stderr, "\n --- x11vnc loop: did %d"
				    " done. ---\n\n", loop_max);
				break;
			}

			fprintf(stderr, "\n --- x11vnc loop: sleeping %d ms "
			    "---\n\n", loop_sleep);
			usleep(loop_sleep * 1000);
		}
		exit(0);
#else
		fprintf(stderr, "fork unavailable, cannot do -loop mode\n");
		exit(1);
#endif
	}
}
