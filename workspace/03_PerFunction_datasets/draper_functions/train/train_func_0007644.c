em28xx_vbi_supported(struct em28xx *dev)
{

	if (disable_vbi == 1)
		return 0;

	if (dev->board.is_webcam)
		return 0;


	if (dev->chip_id == CHIP_ID_EM2860 ||
	    dev->chip_id == CHIP_ID_EM2883)
		return 1;


	return 0;
}
