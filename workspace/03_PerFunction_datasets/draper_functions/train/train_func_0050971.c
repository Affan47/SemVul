loop()
{
	int key;
	if (resize())
		return 1;

	key = sl_getch2();

	switch (state) {
	case A_client:
		client(key);
		break;

	case A_menu:
		menu(key);
		break;

	case A_training:
		if (sk_service(tr_skier, key))
			play(tr_skier);
		else {
			sl_cls();
			state = A_menu;
		}

		break;
	case A_cup:
		cup(key);
		break;

	case A_quit:
		break;

	}

	usleep(0xdead - 0xcafe/0x6);
	sl_refresh();

	return state;
}
