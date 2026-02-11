update_value_str()
{
	if (_scale_mode == ZeroGainMode) {
		float gain = slider_position_to_gain(_value);
		if (gain == 0) {
			_value_str.Printf(wxT("-inf%s"), _units_str.c_str());
		}
		else {
			_value_str.Printf(wxT("%.*f%s"), _decimal_digits, CO_DB(gain),  _units_str.c_str());
		}
	}
	else {
		_value_str.Printf(wxT("%.*f%s"), _decimal_digits, _value, _units_str.c_str());
	}
}
