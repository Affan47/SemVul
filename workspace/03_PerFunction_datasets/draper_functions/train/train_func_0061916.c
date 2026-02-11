smdi_toggle_mwi(struct ast_smdi_interface *iface, const char *mailbox, int on)
{
	FILE *file;
	int i;

	if (!(file = fopen(iface->name, "w"))) {
		ast_log(LOG_ERROR, "Error opening SMDI interface %s (%s) for writing\n", iface->name, strerror(errno));
		return 1;
	}

	ASTOBJ_WRLOCK(iface);

	fprintf(file, "%s:MWI ", on ? "OP" : "RMV");

	for (i = 0; i < iface->msdstrip; i++)
		fprintf(file, "0");

	fprintf(file, "%s!\x04", mailbox);

	fclose(file);

	ASTOBJ_UNLOCK(iface);
	ast_debug(1, "Sent MWI set message for %s on %s\n", mailbox, iface->name);

	return 0;
}
