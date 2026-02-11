lkkbd_detection_done(struct lkkbd *lk)
{
	int i;


	lk->keycode[0xb1] = KEY_COMPOSE;


	switch (lk->id[4]) {
	case 1:
		strlcpy(lk->name, "DEC LK201 keyboard", sizeof(lk->name));

		if (lk201_compose_is_alt)
			lk->keycode[0xb1] = KEY_LEFTALT;
		break;

	case 2:
		strlcpy(lk->name, "DEC LK401 keyboard", sizeof(lk->name));
		break;

	default:
		strlcpy(lk->name, "Unknown DEC keyboard", sizeof(lk->name));
		printk(KERN_ERR
			"lkkbd: keyboard on %s is unknown, please report to "
			"Jan-Benedict Glaw <jbglaw@lug-owl.de>\n", lk->phys);
		printk(KERN_ERR "lkkbd: keyboard ID'ed as:");
		for (i = 0; i < LK_NUM_IGNORE_BYTES; i++)
			printk(" 0x%02x", lk->id[i]);
		printk("\n");
		break;
	}

	printk(KERN_INFO "lkkbd: keyboard on %s identified as: %s\n",
		lk->phys, lk->name);


	switch (lk->id[2]) {
	case 0x00:

		break;

	case LK_STUCK_KEY:
		printk(KERN_ERR "lkkbd: Stuck key on keyboard at %s\n",
			lk->phys);
		break;

	case LK_SELFTEST_FAILED:
		printk(KERN_ERR
			"lkkbd: Selftest failed on keyboard at %s, "
			"keyboard may not work properly\n", lk->phys);
		break;

	default:
		printk(KERN_ERR
			"lkkbd: Unknown error %02x on keyboard at %s\n",
			lk->id[2], lk->phys);
		break;
	}


	if (lk->id[2] == LK_STUCK_KEY && lk->id[3] != 0)
		printk(KERN_ERR
			"Scancode of stuck key is 0x%02x, keycode is 0x%04x\n",
			lk->id[3], lk->keycode[lk->id[3]]);
}
