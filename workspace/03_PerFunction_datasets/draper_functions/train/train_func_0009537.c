tryActivation()
{
#ifdef S5B_DEBUG
	printf("tryActivation\n");
#endif
	if(activated) {
#ifdef S5B_DEBUG
		printf("already activated !?\n");
#endif
		return;
	}

	if(targetMode == NotFast) {
#ifdef S5B_DEBUG
		printf("tryActivation: NotFast\n");
#endif

		finished();
	}
	else if(targetMode == Fast) {

		delete task;
		task = 0;

		activated = true;


		if(udp) {
			m->doActivate(peer, sid, activatedStream);
		}
		else {
#ifdef S5B_DEBUG
			printf("sending extra CR\n");
#endif

			QByteArray a(1);
			a[0] = '\r';
			client->write(a);
		}
	}
}
