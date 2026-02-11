onMouseButtonDown(MouseEventArgs& e)
{

	PushButton::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{

		d_beingDragged = true;
		d_dragPoint = CoordConverter::screenToWindow(*this, e.position);


		WindowEventArgs args(this);
		onThumbTrackStarted(args);

		++e.handled;
	}

}
