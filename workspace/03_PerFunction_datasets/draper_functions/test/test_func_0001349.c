ath9k_hw_wow_apply_pattern(struct ath_hw *ah, u8 *user_pattern,
			       u8 *user_mask, int pattern_count,
			       int pattern_len)
{
	int i;
	u32 pattern_val, mask_val;
	u32 set, clr;

	if (pattern_count >= ah->wow.max_patterns)
		return -ENOSPC;

	if (pattern_count < MAX_NUM_PATTERN_LEGACY)
		REG_SET_BIT(ah, AR_WOW_PATTERN, BIT(pattern_count));
	else
		REG_SET_BIT(ah, AR_MAC_PCU_WOW4, BIT(pattern_count - 8));

	for (i = 0; i < MAX_PATTERN_SIZE; i += 4) {
		memcpy(&pattern_val, user_pattern, 4);
		REG_WRITE(ah, (AR_WOW_TB_PATTERN(pattern_count) + i),
			  pattern_val);
		user_pattern += 4;
	}

	for (i = 0; i < MAX_PATTERN_MASK_SIZE; i += 4) {
		memcpy(&mask_val, user_mask, 4);
		REG_WRITE(ah, (AR_WOW_TB_MASK(pattern_count) + i), mask_val);
		user_mask += 4;
	}

	if (pattern_count < MAX_NUM_PATTERN_LEGACY)
		ah->wow.wow_event_mask |=
			BIT(pattern_count + AR_WOW_PAT_FOUND_SHIFT);
	else
		ah->wow.wow_event_mask2 |=
			BIT((pattern_count - 8) + AR_WOW_PAT_FOUND_SHIFT);

	if (pattern_count < 4) {
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN1_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH1_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH1, set, clr);
	} else if (pattern_count < 8) {
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN2_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH2_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH2, set, clr);
	} else if (pattern_count < 12) {
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN3_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH3_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH3, set, clr);
	} else if (pattern_count < MAX_NUM_PATTERN) {
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN4_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH4_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH4, set, clr);
	}

	return 0;
}
