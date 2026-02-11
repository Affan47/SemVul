hkl_interval_tan(HklInterval *self)
{
	int quadrant_down = (int)floor(self->min / M_PI_2);
	int quadrant_up = (int)floor(self->max / M_PI_2);


	if ( ((quadrant_up - quadrant_down) >= 2)
	     || (!(quadrant_down % 2) && (quadrant_up % 2)) ) {
		self->min = -INFINITY;
		self->max = INFINITY;
	} else {
		self->min = tan(self->min);
		self->max = tan(self->max);
	}
}
