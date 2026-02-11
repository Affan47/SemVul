adjust_value (gfloat increment)
{
	gfloat val;
	bool done = false;

	val = adjustment.get_value();

	val += increment;

	if (val > upper) {
		if (wrap) {
			val = lower;
		} else {
			val = upper;
			done = true;
		}
	} else if (val < lower) {
		if (wrap) {
			val = upper;
		} else {
			val = lower;
			done = true;
		}
	}

	set_value(val);
	return done;
}
