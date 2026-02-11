_rtl8723e_phy_simularity_compare(struct ieee80211_hw *hw,
					     long result[][8], u8 c1, u8 c2)
{
	u32 i, j, diff, simularity_bitmap, bound;

	u8 final_candidate[2] = { 0xFF, 0xFF };
	bool bresult = true;

	bound = 4;

	simularity_bitmap = 0;

	for (i = 0; i < bound; i++) {
		diff = (result[c1][i] > result[c2][i]) ?
		    (result[c1][i] - result[c2][i]) :
		    (result[c2][i] - result[c1][i]);

		if (diff > MAX_TOLERANCE) {
			if ((i == 2 || i == 6) && !simularity_bitmap) {
				if (result[c1][i] + result[c1][i + 1] == 0)
					final_candidate[(i / 4)] = c2;
				else if (result[c2][i] + result[c2][i + 1] == 0)
					final_candidate[(i / 4)] = c1;
				else
					simularity_bitmap = simularity_bitmap |
					    (1 << i);
			} else
				simularity_bitmap =
				    simularity_bitmap | (1 << i);
		}
	}

	if (simularity_bitmap == 0) {
		for (i = 0; i < (bound / 4); i++) {
			if (final_candidate[i] != 0xFF) {
				for (j = i * 4; j < (i + 1) * 4 - 2; j++)
					result[3][j] =
					    result[final_candidate[i]][j];
				bresult = false;
			}
		}
		return bresult;
	} else if (!(simularity_bitmap & 0x0F)) {
		for (i = 0; i < 4; i++)
			result[3][i] = result[c1][i];
		return false;
	} else {
		return false;
	}

}
