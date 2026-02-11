axis_position_zeroaxis(AXIS_INDEX axis)
{
    TBOOLEAN is_inside = FALSE;
    AXIS *this = axis_array + axis;


    if ((this->min > 0.0 && this->max > 0.0)
	|| this->log) {
	this->term_zero = (this->max < this->min)
	    ? this->term_upper : this->term_lower;
    } else if (this->min < 0.0 && this->max < 0.0) {
	this->term_zero = (this->max < this->min)
	    ? this->term_lower : this->term_upper;
    } else {
	this->term_zero = AXIS_MAP(axis, 0.0);
	is_inside = TRUE;
    }

    return is_inside;
}
