new_frame
	(
	)
	{
	if (selected < 0)
		return;
	int shnum = info[selected].shapenum,
	    frnum = info[selected].framenum;
	Vga_file *ifile = file_info->get_ifile();

	Shape *shape = ifile->extract_shape(shnum);
	if (!shape ||

	    frnum > shape->get_num_frames())
		return;

	ExultStudio *studio = ExultStudio::get_instance();
	bool flat = shnum < 0x96 && file_info == studio->get_vgafile();
	int w = 0, h = 0;
	int xleft, yabove;
	if (flat)
		w = h = xleft = yabove = 8;
	else
		{
		int cnt = shape->get_num_frames();
		for (int i = 0; i < cnt; i++)
			{
			int ht = shape->get_frame(i)->get_height();
			if (ht > h)
				h = ht;
			int wd = shape->get_frame(i)->get_width();
			if (wd > w)
				w = wd;
			}
		if (h == 0)
			h = 8;
		if (w == 0)
			w = 8;
		xleft = w - 1;
		yabove = h - 1;
		}
	Image_buffer8 img(w, h);
	img.fill8(1);
	if (w > 2 && h > 2)
		img.fill8(2, w - 2, h - 2, 1, 1);
	Shape_frame *frame = new Shape_frame(img.get_bits(),
			w, h, xleft, yabove, !flat);
	shape->add_frame(frame, frnum + 1);
	file_info->set_modified();
	Object_browser *browser = studio->get_browser();
	if (browser)
		{
		browser->render();
		browser->show();
		}
	studio->update_group_windows(0);
	}
