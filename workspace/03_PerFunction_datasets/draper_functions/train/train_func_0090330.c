apds990x_detect(struct apds990x_chip *chip)
{
	struct i2c_client *client = chip->client;
	int ret;
	u8 id;

	ret = apds990x_read_byte(chip, APDS990X_ID, &id);
	if (ret < 0) {
		dev_err(&client->dev, "ID read failed\n");
		return ret;
	}

	ret = apds990x_read_byte(chip, APDS990X_REV, &chip->revision);
	if (ret < 0) {
		dev_err(&client->dev, "REV read failed\n");
		return ret;
	}

	switch (id) {
	case APDS990X_ID_0:
	case APDS990X_ID_4:
	case APDS990X_ID_29:
		snprintf(chip->chipname, sizeof(chip->chipname), "APDS-990x");
		break;
	default:
		ret = -ENODEV;
		break;
	}
	return ret;
}
