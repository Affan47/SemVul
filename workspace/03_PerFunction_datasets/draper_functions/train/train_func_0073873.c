file_open_dialog(char **name, uint *mode)
{
	Bounds b, c;

	app->getbounds(&b);

	c = b;
	b.w = 60;
	b.h = 20;
	b.x = (c.w - b.w) / 2,
	b.y = (c.h - b.h) / 2;

	c = b;
	c.x = 0;
	c.y = 0;
	c.w -= 2;
	c.h -= 5;


	char cwd[HT_NAME_MAX];
	strcpy(cwd, "local:");
	if (!getcwd(cwd+6, (sizeof cwd)-6)) {
		cwd[6] = 0;
	}

	FileBrowser *d = new FileBrowser();
	d->init(&b, &c, "open file", cwd);

	List *hist = (List*)getAtomValue(HISTATOM_FILE);


	c = b;
	c.x = 6;
	c.y = b.h-4;
	c.w = 12;
	c.h = 1;

	ht_listpopup *mode_input = new ht_listpopup();
	mode_input->init(&c);

	mode_input->insertstring("autodetect");
	mode_input->insertstring("binary");
	mode_input->insertstring("text");

	mode_input->growmode = MK_GM(GMH_LEFT, GMV_BOTTOM);

	d->insert(mode_input);


	c = b;
	c.x = 1;
	c.y = b.h-4;
	c.w = 9;
	c.h = 1;

	ht_label *mode_text = new ht_label();
	mode_text->init(&c, "~mode", mode_input);
	mode_text->growmode = MK_GM(GMH_LEFT, GMV_BOTTOM);

	d->insert(mode_text);


	if (d->run(false)) {
		struct {
			FileBrowserData browser;
			ht_listpopup_data mode;
		} data;

		ViewDataBuf vdb(d, &data, sizeof data);

		char buf[VFS_URL_MAX];
		d->extract_url(buf);


		if (ht_strncmp(buf, "local:", 6) == 0) {
			*name = ht_strdup(buf+6);

			if (hist) insert_history_entry(hist, *name, 0);

			switch (data.mode.cursor_pos) {
				case 0: *mode=FOM_AUTO; break;
				case 1: *mode=FOM_BIN; break;
				case 2: *mode=FOM_TEXT; break;
			}

			d->done();
			delete d;
			return true;
		}
	}
	d->done();
	delete d;
	return false;
}
