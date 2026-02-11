handle_hsv_property(CCOLOR *_object, void *_param, int prop)
{
  int h, s, v;
  gt_rgb_to_hsv_cached(THIS->r, THIS->g, THIS->b, &h, &s, &v);

	if (READ_PROPERTY)
	{
		switch(prop)
		{
			case CC_H: GB.ReturnInteger(h); break;
			case CC_V: GB.ReturnInteger(v); break;
			case CC_S: GB.ReturnInteger(s); break;
		}
	}
	else
	{
		switch(prop)
		{
			case CC_H: h = VPROP(GB_INTEGER) % 360; break;
			case CC_V: v = VPROP(GB_INTEGER); if (v < 0) v = 0; else if (v > 255) v = 255; break;
			case CC_S: s = VPROP(GB_INTEGER); if (s < 0) s = 0; else if (s > 255) s = 255; break;
		}
		COLOR_hsv_to_rgb(h, s, v, &THIS->r, &THIS->g, &THIS->b);
	}
}
