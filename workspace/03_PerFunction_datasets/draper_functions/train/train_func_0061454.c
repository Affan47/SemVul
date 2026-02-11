pd_print_error(struct pd_unit *disk, char *msg, int status)
{
	int i;

	printk("%s: %s: status = 0x%x =", disk->name, msg, status);
	for (i = 0; i < ARRAY_SIZE(pd_errs); i++)
		if (status & (1 << i))
			printk(" %s", pd_errs[i]);
	printk("\n");
}
