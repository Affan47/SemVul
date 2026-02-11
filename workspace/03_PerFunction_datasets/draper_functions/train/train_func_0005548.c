init(Bounds *b, int options, List *history)
{
	ht_group::init(b, VO_SELECTABLE, NULL);
	VIEW_DEBUG_NAME("ht_replace_hexascii_search_form");

	Bounds c;

	c.x=6;
	c.y=0;
	c.w=40;
	c.h=1;
	str=new ht_strinputfield();
	str->init(&c, 64, history);
	insert(str);

	c.x=0;
	c.w=5;
	c.h=1;
	ht_label *strlabel=new ht_label();
	strlabel->init(&c, "~ascii", str);
	insert(strlabel);


	c.x=6;
	c.y=2;
	c.w=40;
	c.h=1;
	ht_hexinputfield *hex=new ht_hexinputfield();
	hex->init(&c, 64);
	hex->attach(str);
	insert(hex);

	c.x=0;
	c.w=5;
	c.h=1;
	ht_label *hexlabel=new ht_label();
	hexlabel->init(&c, "~hex", hex);
	insert(hexlabel);
}
