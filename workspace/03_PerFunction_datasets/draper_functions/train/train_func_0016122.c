get_total_number_places(double end, int decimal_places) {
	if (decimal_places > 0)
		return log10(end) + 2 + decimal_places;
	else
		return log10(end) + 1;
}
