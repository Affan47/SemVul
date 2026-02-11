draw_ind(wxDC & dc)
{
	int pixw;

	dc.SetPen(*wxTRANSPARENT_PEN);

	if (_bar_style == FromLeftStyle)
	{
		pixw = (int) ((_ind_value - _lower_bound) / _val_scale);
		if (pixw > 0) {
			if (_ind_value >= _upper_bound) {
				dc.SetBrush(_indmaxbrush);
			}
			else {
				dc.SetBrush(_indbrush);
			}
			dc.DrawRectangle (1, 1, pixw-1, 1);
			dc.DrawRectangle (1, _height - 2, pixw-1, 1);
		}

	}
	else if (_bar_style == FromRightStyle)
	{
		pixw = (int) ((_upper_bound - _ind_value) / _val_scale);
		if (pixw < _width) {
			if (_ind_value >= _upper_bound) {
				dc.SetBrush(_indmaxbrush);
			}
			else {
				dc.SetBrush(_indbrush);
			}
			dc.DrawRectangle (pixw, 1, _width - pixw -1, 2);
			dc.DrawRectangle (pixw, _height - 2, _width - pixw - 1, 1);
		}
	}

	pixw = (int) ((_ind_value - _lower_bound) / _val_scale);
	if (pixw > 0) {
		if (_ind_value >= _upper_bound) {
			dc.SetBrush(_indmaxbrush);
		}
		else {
			dc.SetBrush(_indbrush);
		}
		dc.DrawRectangle (pixw - 2, 1, 2, _height-2);
	}
}
