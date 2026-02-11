or51211_reset(struct dvb_frontend * fe)
{
	struct dvb_bt8xx_card *bt = fe->dvb->priv;


	int ret = bttv_gpio_enable(bt->bttv_nr, 0x001F, 0x001F);
	if (ret != 0)
		printk(KERN_WARNING "or51211: Init Error - Can't Reset DVR (%i)\n", ret);
	bttv_write_gpio(bt->bttv_nr, 0x001F, 0x0000);
	msleep(20);

	bttv_write_gpio(bt->bttv_nr, 0x0001F, 0x0001);

	msleep(500);
}
