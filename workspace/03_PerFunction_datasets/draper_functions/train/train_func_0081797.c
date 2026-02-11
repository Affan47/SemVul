init(Bounds *b, const char *desc, uint framestyle, uint number, ht_project **p)
{
	ht_window::init(b, desc, framestyle, number);
	project = p;

	Bounds c = *b;
	c.x = 0;
	c.y = 0;
	c.w -= 2;
	c.h -= 2;
	plb = new ht_project_listbox();
	plb->init(&c, *p);

	insert(plb);
	sendmsg(msg_project_changed);
}
