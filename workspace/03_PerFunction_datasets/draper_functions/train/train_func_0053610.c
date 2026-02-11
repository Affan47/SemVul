set_level(struct tca6507_chip *tca, int bank, int level)
{
	switch (bank) {
	case BANK0:
	case BANK1:
		set_code(tca, TCA6507_MAX_INTENSITY, bank, level);
		break;
	case MASTER:
		set_code(tca, TCA6507_MASTER_INTENSITY, 0, level);
		break;
	}
	tca->bank[bank].level = level;
}
