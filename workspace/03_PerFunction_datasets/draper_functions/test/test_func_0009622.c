data_search_comparison_result(int cmpval,
	enum data_search_comparison comparison_type)
{
	switch (comparison_type) {
	case DATA_CMP_GE:
		if (cmpval >= 0) {
			return 0;
		}
		break;
	case DATA_CMP_LE:
		if (cmpval <= 0) {
			return 0;
		}
		break;
	case DATA_CMP_EQ:
		if (cmpval == 0) {
			return 0;
		}
		break;
	case DATA_CMP_NEQ:
		if (cmpval != 0) {
			return 0;
		}
		break;
	case DATA_CMP_LT:
		if (cmpval < 0) {
			return 0;
		}
		break;
	case DATA_CMP_GT:
		if (cmpval > 0) {
			return 0;
		}
		break;
	case DATA_CMP_UNKNOWN:
		break;
	}
	return 1;
}
