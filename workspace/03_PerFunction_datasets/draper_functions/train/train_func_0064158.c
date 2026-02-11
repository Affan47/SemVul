setHorzRange(float min, float max)
{
    Size parentSize(getParentPixelSize());


	if (min > max)
	{
		float tmp = min;
		max = min;
		min = tmp;
	}

	d_horzMax = max;
	d_horzMin = min;


	float cp = getXPosition().asAbsolute(parentSize.d_width);

	if (cp < min)
	{
		setXPosition(cegui_absdim(min));
	}
	else if (cp > max)
	{
		setXPosition(cegui_absdim(max));
	}

}
