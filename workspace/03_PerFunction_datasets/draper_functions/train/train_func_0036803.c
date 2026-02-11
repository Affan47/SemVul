inputboxrect(Bounds *b, const char *title, const char *label, char *result, int limit, uint32 histid)
{
	ht_dialog *dialog=new ht_dialog();
	dialog->init(b, title, FS_KILLER | FS_TITLE | FS_MOVE | FS_RESIZE);

	ht_strinputfield *input;

	Bounds  b2;
	b2.x = 3 + strlen(label);
	b2.y = 1;
	b2.w = b->w - 3 - b2.x;
	b2.h = 1;

	List *hist = NULL;
	if (histid) hist = (List*)getAtomValue(histid);
	input = new ht_strinputfield();
	input->init(&b2, limit, hist);
	ht_inputfield_data d;
	d.text = (byte *)result;
	d.textlen = strlen((char*)d.text);
	input->databuf_set(&d, sizeof d);
	dialog->insert(input);

	if (label) {
		b2.x = 1;
		b2.y = 1;
		b2.w = 3 + strlen(label) - b2.x;
		b2.h = 1;

		ht_label *lab = new ht_label();
		lab->init(&b2, label, input);
		dialog->insert(lab);
	}

	b2.x = b->w - 25;
	b2.y = b->h - 5;
	b2.w = 10;
	b2.h = 2;

	ht_button *bok = new ht_button();
	bok->init(&b2, "O~k", button_ok);
	dialog->insert(bok);

	b2.x += 12;

	ht_button *bcancel = new ht_button();
	bcancel->init(&b2, "~Cancel", button_cancel);
	dialog->insert(bcancel);

	if (dialog->run(0)) {
		int dsize = input->datasize();
		ht_inputfield_data *data = ht_malloc(dsize);
		ViewDataBuf vdb(input, data, dsize);
		bin2str(result, data->text, data->textlen);
		free(data);
		if (hist) insert_history_entry(hist, result, 0);

		dialog->done();
		delete dialog;
		return true;
	}
	dialog->done();
	delete dialog;
	return false;
}
