usage(void)
{
	int i;

	printf("hciconfig - HCI device configuration utility\n");
	printf("Usage:\n"
		"\thciconfig\n"
		"\thciconfig [-a] hciX [command ...]\n");
	printf("Commands:\n");
	for (i = 0; command[i].cmd; i++)
		printf("\t%-10s %-8s\t%s\n", command[i].cmd,
		command[i].opt ? command[i].opt : " ",
		command[i].doc);
}
