onMouseMove(MouseEventArgs& e)
{

	PushButton::onMouseMove(e);


	if (d_beingDragged)
	{
        Size parentSize(getParentPixelSize());

		Vector2 delta;
		float hmin, hmax, vmin, vmax;

        delta = CoordConverter::screenToWindow(*this, e.position);

        hmin = d_horzMin;
        hmax = d_horzMax;
        vmin = d_vertMin;
        vmax = d_vertMax;


		delta -= d_dragPoint;
        delta.d_x /= parentSize.d_width;
        delta.d_y /= parentSize.d_height;


		UVector2 newPos(getPosition());

		if (d_horzFree)
		{
			newPos.d_x.d_scale += delta.d_x;


			newPos.d_x.d_scale = (newPos.d_x.d_scale < hmin) ? hmin : (newPos.d_x.d_scale > hmax) ? hmax : newPos.d_x.d_scale;
		}

		if (d_vertFree)
		{
			newPos.d_y.d_scale += delta.d_y;


			newPos.d_y.d_scale = (newPos.d_y.d_scale < vmin) ? vmin : (newPos.d_y.d_scale > vmax) ? vmax : newPos.d_y.d_scale;
		}


		if (newPos != getPosition())
		{
			setPosition(newPos);


			if (d_hotTrack)
			{
				WindowEventArgs args(this);
				onThumbPositionChanged(args);
			}

		}

	}

	++e.handled;
}
