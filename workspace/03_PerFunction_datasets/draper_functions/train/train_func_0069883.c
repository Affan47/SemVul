bolt_pict(int y, int x, int ny, int nx, int typ, byte *a, wchar_t *c)
{
	int motion;


	if ((ny == y) && (nx == x))
		motion = BOLT_NO_MOTION;
	else if (nx == x)
		motion = BOLT_0;
	else if ((ny-y) == (x-nx))
		motion = BOLT_45;
	else if (ny == y)
		motion = BOLT_90;
	else if ((ny-y) == (nx-x))
		motion = BOLT_135;
	else
		motion = BOLT_NO_MOTION;


	if (use_graphics == GRAPHICS_NONE) {

		wchar_t chars[] = L"*|/-\\";

		*c = chars[motion];
		*a = spell_color(typ);
	} else {
		*a = gf_to_attr[typ][motion];
		*c = gf_to_char[typ][motion];
	}
}
