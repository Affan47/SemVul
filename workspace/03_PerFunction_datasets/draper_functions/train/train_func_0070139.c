dice_card_strings(struct snd_dice *dice)
{
	struct snd_card *card = dice->card;
	struct fw_device *dev = fw_parent_device(dice->unit);
	char vendor[32], model[32];
	unsigned int i;
	int err;

	strcpy(card->driver, "DICE");

	strcpy(card->shortname, "DICE");
	BUILD_BUG_ON(NICK_NAME_SIZE < sizeof(card->shortname));
	err = snd_dice_transaction_read_global(dice, GLOBAL_NICK_NAME,
					       card->shortname,
					       sizeof(card->shortname));
	if (err >= 0) {

		BUILD_BUG_ON(sizeof(card->shortname) % 4 != 0);
		for (i = 0; i < sizeof(card->shortname); i += 4)
			swab32s((u32 *)&card->shortname[i]);
		card->shortname[sizeof(card->shortname) - 1] = '\0';
	}

	strcpy(vendor, "?");
	fw_csr_string(dev->config_rom + 5, CSR_VENDOR, vendor, sizeof(vendor));
	strcpy(model, "?");
	fw_csr_string(dice->unit->directory, CSR_MODEL, model, sizeof(model));
	snprintf(card->longname, sizeof(card->longname),
		 "%s %s (serial %u) at %s, S%d",
		 vendor, model, dev->config_rom[4] & 0x3fffff,
		 dev_name(&dice->unit->device), 100 << dev->max_speed);

	strcpy(card->mixername, "DICE");
}
