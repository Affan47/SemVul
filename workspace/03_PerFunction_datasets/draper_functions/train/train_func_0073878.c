ar5416GetRateTable(struct ath_hal *ah, a_uint32_t mode)
{
	HAL_RATE_TABLE *rt;
	switch (mode) {
	case HAL_MODE_11NG:
		rt = &ar5416_11ng_table;
		break;
#ifdef ATH_SUPPORT_A_MODE
	case HAL_MODE_11NA:
		rt = &ar5416_11na_table;
		break;
#endif
	default:
		return AH_NULL;
	}

	return rt;
}
