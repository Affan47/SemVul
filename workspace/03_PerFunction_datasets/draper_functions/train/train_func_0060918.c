fileAction(
		const char *fileName,
		struct stat *statbuf UNUSED_PARAM,
		void *userData UNUSED_PARAM,
		int depth UNUSED_PARAM)
{
	parser_t *parser;
	char *tokens[3];
	char *pci_slot_name = NULL, *driver = NULL;
	int pci_class = 0, pci_vid = 0, pci_did = 0;
	int pci_subsys_vid = 0, pci_subsys_did = 0;

	char *uevent_filename = concat_path_file(fileName, "/uevent");
	parser = config_open2(uevent_filename, fopen_for_read);
	free(uevent_filename);

	while (config_read(parser, tokens, 3, 2, "\0:=", PARSE_NORMAL)) {
		if (strcmp(tokens[0], "DRIVER") == 0) {
			driver = xstrdup(tokens[1]);
			continue;
		}

		if (strcmp(tokens[0], "PCI_CLASS") == 0) {
			pci_class = xstrtou(tokens[1], 16)>>8;
			continue;
		}

		if (strcmp(tokens[0], "PCI_ID") == 0) {
			pci_vid = xstrtou(tokens[1], 16);
			pci_did = xstrtou(tokens[2], 16);
			continue;
		}

		if (strcmp(tokens[0], "PCI_SUBSYS_ID") == 0) {
			pci_subsys_vid = xstrtou(tokens[1], 16);
			pci_subsys_did = xstrtou(tokens[2], 16);
			continue;
		}

		if (strcmp(tokens[0], "PCI_SLOT_NAME") == 0) {
			pci_slot_name = xstrdup(tokens[2]);
			continue;
		}
	}
	config_close(parser);


	if (option_mask32 & OPT_m) {
		printf("%s \"Class %04x\" \"%04x\" \"%04x\" \"%04x\" \"%04x\"",
		       pci_slot_name, pci_class, pci_vid, pci_did,
		       pci_subsys_vid, pci_subsys_did);
	} else {
		printf("%s Class %04x: %04x:%04x",
		       pci_slot_name, pci_class, pci_vid, pci_did);
	}

	if ((option_mask32 & OPT_k) && driver) {
		if (option_mask32 & OPT_m) {
			printf(" \"%s\"", driver);
		} else {
			printf(" %s", driver);
		}
	}
	bb_putchar('\n');

	free(driver);
	free(pci_slot_name);

	return TRUE;
}
