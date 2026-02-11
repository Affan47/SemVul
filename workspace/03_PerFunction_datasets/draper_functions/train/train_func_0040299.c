mouse_control (double x, GdkWindow* window, double scaling)
{
	double fract = 0.0;
	double delta;

	if (window != grab_window) {
		grab_x = x;
		grab_window = window;
		return TRUE;
	}

	delta = x - grab_x;
	grab_x = x;

	switch (_style) {
	case Line:
	case LeftToRight:
		fract = scaling * (delta / (darea.get_width() - 2));
		fract = min (1.0, fract);
		fract = max (-1.0, fract);
		adjustment.set_value (adjustment.get_value() + fract * (adjustment.get_upper() - adjustment.get_lower()));
		break;

	default:
		fract = 0.0;
	}


	return TRUE;
}
