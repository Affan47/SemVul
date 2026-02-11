snd_at73c213_probe(struct spi_device *spi)
{
	struct snd_card			*card;
	struct snd_at73c213		*chip;
	struct at73c213_board_info	*board;
	int				retval;
	char				id[16];

	board = spi->dev.platform_data;
	if (!board) {
		dev_dbg(&spi->dev, "no platform_data\n");
		return -ENXIO;
	}

	if (!board->dac_clk) {
		dev_dbg(&spi->dev, "no DAC clk\n");
		return -ENXIO;
	}

	if (IS_ERR(board->dac_clk)) {
		dev_dbg(&spi->dev, "no DAC clk\n");
		return PTR_ERR(board->dac_clk);
	}


	snprintf(id, sizeof id, "at73c213_%d", board->ssc_id);
	retval = snd_card_new(&spi->dev, -1, id, THIS_MODULE,
			      sizeof(struct snd_at73c213), &card);
	if (retval < 0)
		goto out;

	chip = card->private_data;
	chip->spi = spi;
	chip->board = board;

	chip->ssc = ssc_request(board->ssc_id);
	if (IS_ERR(chip->ssc)) {
		dev_dbg(&spi->dev, "could not get ssc%d device\n",
				board->ssc_id);
		retval = PTR_ERR(chip->ssc);
		goto out_card;
	}

	retval = snd_at73c213_dev_init(card, spi);
	if (retval)
		goto out_ssc;

	strcpy(card->driver, "at73c213");
	strcpy(card->shortname, board->shortname);
	sprintf(card->longname, "%s on irq %d", card->shortname, chip->irq);

	retval = snd_card_register(card);
	if (retval)
		goto out_ssc;

	dev_set_drvdata(&spi->dev, card);

	goto out;

out_ssc:
	ssc_free(chip->ssc);
out_card:
	snd_card_free(card);
out:
	return retval;
}
