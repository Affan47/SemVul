dvb_bt8xx_probe(struct bttv_sub_device *sub)
{
	struct dvb_bt8xx_card *card;
	struct pci_dev* bttv_pci_dev;
	int ret;

	if (!(card = kzalloc(sizeof(struct dvb_bt8xx_card), GFP_KERNEL)))
		return -ENOMEM;

	mutex_init(&card->lock);
	card->bttv_nr = sub->core->nr;
	strlcpy(card->card_name, sub->core->v4l2_dev.name, sizeof(card->card_name));
	card->i2c_adapter = &sub->core->i2c_adap;

	switch(sub->core->type) {
	case BTTV_BOARD_PINNACLESAT:
		card->gpio_mode = 0x0400c060;


		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;
		break;

	case BTTV_BOARD_DVICO_DVBT_LITE:
		card->gpio_mode = 0x0400C060;
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;


		break;

	case BTTV_BOARD_DVICO_FUSIONHDTV_5_LITE:
		card->gpio_mode = 0x0400c060;
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;
		break;

	case BTTV_BOARD_NEBULA_DIGITV:
	case BTTV_BOARD_AVDVBT_761:
		card->gpio_mode = (1 << 26) | (1 << 14) | (1 << 5);
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;

		break;

	case BTTV_BOARD_AVDVBT_771:
		card->gpio_mode = 0x0400402B;
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;

		break;

	case BTTV_BOARD_TWINHAN_DST:
		card->gpio_mode = 0x2204f2c;
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_APABORT | BT878_ARIPERR |
				       BT878_APPERR | BT878_AFBUS;


		break;

	case BTTV_BOARD_PC_HDTV:
		card->gpio_mode = 0x0100EC7B;
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;
		break;

	default:
		pr_err("Unknown bttv card type: %d\n", sub->core->type);
		kfree(card);
		return -ENODEV;
	}

	dprintk("dvb_bt8xx: identified card%d as %s\n", card->bttv_nr, card->card_name);

	if (!(bttv_pci_dev = bttv_get_pcidev(card->bttv_nr))) {
		pr_err("no pci device for card %d\n", card->bttv_nr);
		kfree(card);
		return -ENODEV;
	}

	if (!(card->bt = dvb_bt8xx_878_match(card->bttv_nr, bttv_pci_dev))) {
		pr_err("unable to determine DMA core of card %d,\n", card->bttv_nr);
		pr_err("if you have the ALSA bt87x audio driver installed, try removing it.\n");

		kfree(card);
		return -ENODEV;
	}

	mutex_init(&card->bt->gpio_lock);
	card->bt->bttv_nr = sub->core->nr;

	if ( (ret = dvb_bt8xx_load_card(card, sub->core->type)) ) {
		kfree(card);
		return ret;
	}

	dev_set_drvdata(&sub->dev, card);
	return 0;
}
