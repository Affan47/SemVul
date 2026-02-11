chip_harris_82c55a_power_set(void *_css, unsigned int val)
{
	TRACE(DEBUG_OTHER,  "chip_harris_82c55a power set (%u)\n",val);

	struct css *css = (struct css *) _css;

	css->state_power = val;

	if (val) {

		chip_harris_82c55a_mode_set(css, 0x9b);
	}
}
