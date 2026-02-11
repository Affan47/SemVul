elevator_motor_set(void *_cpssp, unsigned int val)
{
	struct cpssp * cpssp = (struct cpssp *) _cpssp;

	if (val == SIG_STD_LOGIC_0) {
		cpssp->motor_on = 0;
	} else if (val == SIG_STD_LOGIC_1) {
		cpssp->motor_on = 1;
	}
}
