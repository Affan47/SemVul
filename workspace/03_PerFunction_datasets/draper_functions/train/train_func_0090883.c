bright_func(RGBColor c, int scale, int absScale)
{
	RGBColor ans;
	if( scale < 0)
	{
		double factor = sqrt(double(absScale + scale) / absScale);
		ans.red = BYTE(c.red * factor);
		ans.green = BYTE(c.green * factor);
		ans.blue = BYTE(c.blue * factor);
	}
	else
	{
		ans.red = c.red + (MAX_COLOUR - c.red) * scale / absScale;
		ans.green = c.green + (MAX_COLOUR - c.green) * scale / absScale;
		ans.blue = c.blue + (MAX_COLOUR - c.blue) * scale / absScale;
	}
	return ans;
}
