message_read(int fd, int flags, struct message *m)
{
    libspamc_timeout = 0;


    m->priv = malloc(sizeof(struct libspamc_private_message));
    if (m->priv == NULL) {
	libspamc_log(flags, LOG_ERR, "message_read: malloc failed");
	return EX_OSERR;
    }
    m->priv->flags = flags;

    switch (flags & SPAMC_MODE_MASK) {
    case SPAMC_RAW_MODE:
	return _message_read_raw(fd, m);

    case SPAMC_BSMTP_MODE:
	return _message_read_bsmtp(fd, m);

    default:
	libspamc_log(flags, LOG_ERR, "message_read: Unknown mode %d",
		flags & SPAMC_MODE_MASK);
	return EX_USAGE;
    }
}
