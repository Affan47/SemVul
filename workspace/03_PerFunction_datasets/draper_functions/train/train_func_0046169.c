phonebook_write(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[512] = {0x00, 0x01, 0x1f, 0x01, 0x04, 0x87, 0x00};
	gn_phonebook_entry *pe;
	unsigned char *pos;
	int namelen, numlen;

	pe = data->phonebook_entry;
	pos = req + 6;
	namelen = strlen(pe->name);
	numlen = strlen(pe->number);
	dprintf("Writing phonebook location (%d): %s\n", pe->location, pe->name);
	if (namelen > GN_PHONEBOOK_NAME_MAX_LENGTH) {
		dprintf("name too long\n");
		return GN_ERR_ENTRYTOOLONG;
	}
	if (numlen > GN_PHONEBOOK_NUMBER_MAX_LENGTH) {
		dprintf("number too long\n");
		return GN_ERR_ENTRYTOOLONG;
	}
	if (pe->subentries_count > 1) {
		dprintf("6160 doesn't support subentries\n");
		return GN_ERR_UNKNOWN;
	}
	if ((pe->subentries_count == 1) && ((pe->subentries[0].entry_type != GN_PHONEBOOK_ENTRY_Number)
		|| (pe->subentries[0].number_type != GN_PHONEBOOK_NUMBER_General) || (pe->subentries[0].id != 2)
		|| strcmp(pe->subentries[0].data.number, pe->number))) {
		dprintf("6160 doesn't support subentries\n");
		return GN_ERR_UNKNOWN;
	}

	*pos++ = pe->location;
	strcpy(pos, pe->number);
	pos += numlen + 1;
	strcpy(pos, pe->name);
	pos += namelen + 1;

	SEND_MESSAGE_BLOCK(0x40, pos - req);
}
