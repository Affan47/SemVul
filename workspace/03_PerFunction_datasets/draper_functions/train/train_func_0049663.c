addUnit()
{
	for (diag_iter di = diag_begin(); di != diag_end(); ++di) {
		(*di).getAlpha() = *((*di).getAlpha()) + 1.0;
	}
}
