OnMouseEvents (wxMouseEvent &ev)
{
	if (!IsEnabled()) {
		ev.Skip();
		return;
	}

	if (ev.Moving()) {

	}
	else if (ev.RightDown()) {
		if (_popup_menu) {
			this->PopupMenu ( _popup_menu, ev.GetX(), ev.GetY());
		}
		else {
			pressed (get_mouse_button(ev));
		}
	}
	else if (ev.RightUp()) {

		released (get_mouse_button(ev));
	}
	else if (ev.ButtonDown())
	{
		if (!(ev.MiddleDown() && ev.ControlDown())) {
			_bstate = Selected;
			pressed (get_mouse_button(ev));
			CaptureMouse();
			Refresh(false);
		}
	}
	else if (ev.ButtonUp())
	{
		_bstate = Normal;
		ReleaseMouse();
		released (get_mouse_button(ev));

		wxPoint pt = ev.GetPosition();
		wxRect bounds = GetRect();
		pt.x += bounds.x;
		pt.y += bounds.y;

		if (bounds.Inside(pt)) {
			clicked (get_mouse_button(ev));

			if (ev.MiddleUp() && ev.ControlDown()) {
				bind_request();
			}
		}

		Refresh(false);
	}
	else if (ev.ButtonDClick()) {
		_bstate = Selected;
		pressed (get_mouse_button(ev));
		Refresh(false);
	}
	else if (ev.Entering())
	{
		_estate = Inside;
		enter();
		Refresh(false);
	}
	else if (ev.Leaving())
	{
		_estate = Outside;
		leave();
		Refresh(false);
	}

	ev.Skip();
}
