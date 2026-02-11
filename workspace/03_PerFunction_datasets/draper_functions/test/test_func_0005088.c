do_permaddr(struct cmd_context *ctx)
{
	int i, err;
	struct ethtool_perm_addr *epaddr;

	epaddr = malloc(sizeof(struct ethtool_perm_addr) + MAX_ADDR_LEN);
	epaddr->cmd = ETHTOOL_GPERMADDR;
	epaddr->size = MAX_ADDR_LEN;

	err = send_ioctl(ctx, epaddr);
	if (err < 0)
		perror("Cannot read permanent address");
	else {
		printf("Permanent address:");
		for (i = 0; i < epaddr->size; i++)
			printf("%c%02x", (i == 0) ? ' ' : ':',
			       epaddr->data[i]);
		printf("\n");
	}
	free(epaddr);

	return err;
}
