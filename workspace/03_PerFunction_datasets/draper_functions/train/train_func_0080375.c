snd_client_open(client_t *client)
{
	int err;
	snd_client_open_request_t req;
	snd_client_open_answer_t ans;
	char *name;
	memset(&ans, 0, sizeof(ans));
	err = read(client->ctrl_fd, &req, sizeof(req));
	if (err < 0) {
		SYSERROR("read failed");
		exit(1);
	}
	if (err != sizeof(req)) {
		ans.result = -EINVAL;
		goto _answer;
	}
	name = alloca(req.namelen);
	err = read(client->ctrl_fd, name, req.namelen);
	if (err < 0) {
		SYSERROR("read failed");
		exit(1);
	}
	if (err != req.namelen) {
		ans.result = -EINVAL;
		goto _answer;
	}

	switch (req.transport_type) {
	case SND_TRANSPORT_TYPE_SHM:
		if (!client->local) {
			ans.result = -EINVAL;
			goto _answer;
		}
		switch (req.dev_type) {
		case SND_DEV_TYPE_PCM:
			client->ops = &pcm_shm_ops;
			break;
		case SND_DEV_TYPE_CONTROL:
			client->ops = &ctl_shm_ops;
			break;
		default:
			ans.result = -EINVAL;
			goto _answer;
		}
		break;
	default:
		ans.result = -EINVAL;
		goto _answer;
	}

	name[req.namelen] = '\0';

	client->transport_type = req.transport_type;
	strcpy(client->name, name);
	client->stream = req.stream;
	client->mode = req.mode;

	err = client->ops->open(client, &ans.cookie);
	if (err < 0) {
		ans.result = err;
	} else {
		client->open = 1;
		ans.result = 0;
	}

 _answer:
	err = write(client->ctrl_fd, &ans, sizeof(ans));
	if (err != sizeof(ans)) {
		SYSERROR("write failed");
		exit(1);
	}
	return 0;
}
