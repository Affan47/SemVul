draw_deco_head(int deco, float x, float y, int stem)
{
	struct deco_def_s *dd;
	char *str;

	if (deco == 0)
		return 0;
	dd = &deco_def_tb[deco];
	if (dd->ps_func < 0)
		return 0;
	if (cfmt.setdefl) {
		int fl;

		fl = stem >= 0 ? DEF_STEMUP : 0;
		if (defl != fl) {
			defl = fl;
			PUT1("/defl %d def ", fl);
		}
	}
	switch (dd->func) {
	case 2:
	case 5:
	case 7:
		PUT0("0 ");
		break;
	case 3:
	case 4:
		if (dd->str == 0)
			break;

	case 6:
		str = dd->name;
		if (dd->str != 0 && dd->str != 255)
			str = str_tb[dd->str];
		PUT1("(%s)", str);
		break;
	}
	putxy(x, y);
	PUT1("%s ", ps_func_tb[dd->ps_func]);
	return strncmp(dd->name, "head-", 5) == 0;
}
