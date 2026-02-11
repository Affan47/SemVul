bttv_read_gpio(unsigned int card, unsigned long *data)
{
	struct bttv *btv;

	if (card >= bttv_num) {
		return -EINVAL;
	}

	btv = bttvs[card];
	if (!btv)
		return -ENODEV;

	if(btv->shutdown) {
		return -ENODEV;
	}


	*data = gpio_read();
	return 0;
}
