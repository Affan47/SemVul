get_target_port_group_support(int fd)
{
	struct inquiry_data	inq;
	int			rc;

	memset((unsigned char *)&inq, 0, sizeof(inq));
	rc = do_inquiry(fd, 0, 0x00, &inq, sizeof(inq));
	if (!rc) {
		rc = inquiry_data_get_tpgs(&inq);
	}

	return rc;
}
