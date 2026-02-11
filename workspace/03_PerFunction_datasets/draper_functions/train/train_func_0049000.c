initSegmentHoverState(void)
{

	if (d_splitterHover)
	{
		d_splitterHover = false;
		MouseCursor::getSingleton().setImage(getMouseCursor());
		invalidate();
	}


	if ((!d_segmentHover) && isClickable())
	{
		d_segmentHover = true;
		invalidate();
	}
}
