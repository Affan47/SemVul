pio2_int(int level, int vector, void *ptr)
{
	int vec, i, channel, retval;
	u8 reg;
	struct pio2_card *card  = ptr;

	vec = vector & ~PIO2_VME_VECTOR_MASK;

	switch (vec) {
	case 0:
		dev_warn(&card->vdev->dev, "Spurious Interrupt\n");
		break;
	case 1:
	case 2:
	case 3:
	case 4:

		retval = vme_master_read(card->window, &reg, 1,
			PIO2_REGS_INT_STAT[vec - 1]);
		if (retval < 0) {
			dev_err(&card->vdev->dev,
				"Unable to read IRQ status register\n");
			return;
		}
		for (i = 0; i < 8; i++) {
			channel = ((vec - 1) * 8) + i;
			if (reg & PIO2_CHANNEL_BIT[channel])
				dev_info(&card->vdev->dev,
					"Interrupt on I/O channel %d\n",
					channel);
		}
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:

		dev_err(&card->vdev->dev,
			"Counter interrupt\n");
		break;
	}
}
