__usage_cmd(const struct cmd *cmd, char *indent, bool full)
{
	const char *start, *lend, *end;

	printf("%s", indent);

	switch (cmd->idby) {
	case CIB_NONE:
		break;
	case CIB_PHY:
		printf("phy <phyname> ");
		break;
	case CIB_NETDEV:
		printf("dev <devname> ");
		break;
	}
	if (cmd->parent && cmd->parent->name)
		printf("%s ", cmd->parent->name);
	printf("%s", cmd->name);
	if (cmd->args)
		printf(" %s", cmd->args);
	printf("\n");

	if (!full || !cmd->help)
		return;


	if (strlen(indent))
		indent = "\t\t";
	else
		printf("\n");


	start = cmd->help;
	end = strchr(start, '\0');
	do {
		lend = strchr(start, '\n');
		if (!lend)
			lend = end;
		printf("%s", indent);
		printf("%.*s\n", (int)(lend - start), start);
		start = lend + 1;
	} while (end != lend);

	printf("\n");
}
