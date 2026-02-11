GMT_set_measure_unit (char unit) {


	switch (unit) {
		case 'm':
		case 'M':
			gmtdefs.measure_unit = GMT_M;
			break;
		case 'i':
		case 'I':
			gmtdefs.measure_unit = GMT_INCH;
			break;
		case 'c':
		case 'C':
			gmtdefs.measure_unit = GMT_CM;
			break;
		case 'p':
		case 'P':
			gmtdefs.measure_unit = GMT_PT;
			break;
		default:
			return (GMT_MAP_BAD_MEASURE_UNIT);
	}
	return (GMT_NOERROR);
}
