putxy(float x, float y)
{
	if (scale_voice)
		PUT2("%.1f %.1f ",
		     x / cur_scale, y / cur_scale);
	else
		PUT2("%.1f %.1f ",
		     x / cur_scale, y - cur_trans);
}
