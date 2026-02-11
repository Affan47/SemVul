init(Bounds *b, const char *title)
{
	ht_dialog::init(b, title, FS_KILLER | FS_TITLE | FS_MOVE);
	VIEW_DEBUG_NAME("ht_search_dialog");

	smodecount = 0;
	smodeidx = -1;

	Bounds c;
	c.x=1;
	c.y=1;
	c.w=20;
	c.h=1;

	search_mode_popup = new ht_listpopup();
	search_mode_popup->init(&c);
	insert(search_mode_popup);

	c.x=1;
	c.y=0;
	c.w=4;
	c.h=1;
	ht_label *mlabel=new ht_label();
	mlabel->init(&c, "~mode", search_mode_popup);
	insert(mlabel);

	c.x = 1;
	c.y = 3;
	c.w = size.w-4;
	c.h = MIN(10, size.h-4);
	search_mode_xgroup = new ht_xgroup();
	search_mode_xgroup->init(&c, VO_SELECTABLE, "modes");
	insert(search_mode_xgroup);
}
