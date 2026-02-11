lx_init_xilinx_reset(struct lx6464es *chip)
{
	int i;
	u32 plx_reg = lx_plx_reg_read(chip, ePLX_CHIPSC);

	dev_dbg(chip->card->dev, "->lx_init_xilinx_reset\n");


	plx_reg &= ~CHIPSC_RESET_XILINX;

	lx_plx_reg_write(chip, ePLX_CHIPSC, plx_reg);
	msleep(1);

	lx_plx_reg_write(chip, ePLX_MBOX3, 0);
	msleep(1);

	plx_reg |= CHIPSC_RESET_XILINX;
	lx_plx_reg_write(chip, ePLX_CHIPSC, plx_reg);


	for (i = 0; i != 100; ++i) {
		u32 reg_mbox3;
		msleep(10);
		reg_mbox3 = lx_plx_reg_read(chip, ePLX_MBOX3);
		if (reg_mbox3) {
			dev_dbg(chip->card->dev, "xilinx reset done\n");
			dev_dbg(chip->card->dev, "xilinx took %d loops\n", i);
			break;
		}
	}


	lx_dsp_reg_write(chip, eReg_CSM, 0);


	msleep(600);

	return 0;
}
