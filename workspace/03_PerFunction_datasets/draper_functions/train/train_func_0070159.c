acquirespool(struct qitem *it)
{
	int queuefd;

	if (it->queuef == NULL) {
		queuefd = open_locked(it->queuefn, O_RDWR|O_NONBLOCK);
		if (queuefd < 0)
			goto fail;
		it->queuef = fdopen(queuefd, "r+");
		if (it->queuef == NULL)
			goto fail;
	}

	if (it->mailf == NULL) {
		it->mailf = fopen(it->mailfn, "r");
		if (it->mailf == NULL)
			goto fail;
	}

	return (0);

fail:
	syslog(LOG_INFO, "could not acquire queue file: %m");
	return (-1);
}
