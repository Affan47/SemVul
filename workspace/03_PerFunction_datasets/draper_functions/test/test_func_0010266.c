UT_UCS4_isdigit(UT_UCS4Char c)
{
	if (c < 0x700) {
		for (unsigned int i=0; i < G_N_ELEMENTS(digits_table); i++) {
			if (c < digits_table[i].low) break;
			if (c <= digits_table[i].high)
				return true;
		}
	} else {
		ucs_range * rng = static_cast<ucs_range *>(bsearch(&c, &digits_table,
			G_N_ELEMENTS(digits_table),sizeof(ucs_range),s_cmp_digits));
		if (rng) return true;
	}
	return false;
}
