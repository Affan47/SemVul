bq2415x_detect_revision(struct bq2415x_device *bq)
{
	int ret = bq2415x_exec_command(bq, BQ2415X_REVISION);
	int chip = bq2415x_detect_chip(bq);

	if (ret < 0 || chip < 0)
		return -1;

	switch (chip) {
	case BQ24150:
	case BQ24150A:
	case BQ24151:
	case BQ24151A:
	case BQ24152:
		if (ret >= 0 && ret <= 3)
			return ret;
		return -1;
	case BQ24153:
	case BQ24153A:
	case BQ24156:
	case BQ24156A:
	case BQ24157S:
	case BQ24158:
		if (ret == 3)
			return 0;
		else if (ret == 1)
			return 1;
		return -1;
	case BQ24155:
		if (ret == 3)
			return 3;
		return -1;
	case BQUNKNOWN:
		return -1;
	}

	return -1;
}
