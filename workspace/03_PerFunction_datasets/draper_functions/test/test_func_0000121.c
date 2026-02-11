dt_inflen (const DateStep *step)
{
	switch (step->unit) {
	case DS_DAYS:
		return step->n;
	case DS_MONTHS:
		return step->n * 28;
	default:
		return go_pinf;
	}
}
