set_hue(double hue)
{
	Gdk::Color color;
	color.set_hsv(hue * 360.0, m_saturation, m_value);
	set_color(color);
}
