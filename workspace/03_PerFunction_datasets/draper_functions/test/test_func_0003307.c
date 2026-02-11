copy_from_creg_data(struct rsxx_cardinfo *card,
				int cnt8,
				void *buf,
				unsigned int stream)
{
	int i = 0;
	u32 *data = buf;

	if (unlikely(card->eeh_state))
		return -EIO;

	for (i = 0; cnt8 > 0; i++, cnt8 -= 4) {


		if (LITTLE_ENDIAN && stream)
			data[i] = ioread32be(card->regmap + CREG_DATA(i));
		else
			data[i] = ioread32(card->regmap + CREG_DATA(i));
	}

	return 0;
}
