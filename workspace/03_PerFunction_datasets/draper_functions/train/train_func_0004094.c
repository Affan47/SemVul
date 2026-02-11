initDragMoving(void)
{
	if (d_movingEnabled)
	{

		d_dragMoving = true;
		d_segmentPushed = false;
		d_segmentHover = false;
		d_dragPosition.d_x = 0.0f;
		d_dragPosition.d_y = 0.0f;


		MouseCursor::getSingleton().setImage(d_movingMouseCursor);


		WindowEventArgs args(this);
		onSegmentDragStart(args);
	}

}
