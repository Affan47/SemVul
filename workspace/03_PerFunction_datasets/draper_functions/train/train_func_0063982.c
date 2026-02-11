crypt_random_init(struct crypt_device *ctx)
{
	if (random_initialised)
		return 0;


	if(urandom_fd == -1)
		urandom_fd = open(URANDOM_DEVICE, O_RDONLY);
	if(urandom_fd == -1)
		goto fail;


	if(random_fd == -1)
		random_fd = open(RANDOM_DEVICE, O_RDONLY | O_NONBLOCK);
	if(random_fd == -1)
		goto fail;

	random_initialised = 1;
	return 0;
fail:
	crypt_random_exit();
	log_err(ctx, _("Fatal error during RNG initialisation.\n"));
	return -ENOSYS;
}
