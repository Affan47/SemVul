mn_to_reg(struct mn *mn, u32 m, u32 n, u32 val)
{
	u32 mask;

	mask = MNCTR_MODE_MASK << mn->mnctr_mode_shift;
	mask |= BIT(mn->mnctr_en_bit);
	val &= ~mask;

	if (n) {
		val |= BIT(mn->mnctr_en_bit);
		val |= MNCTR_MODE_DUAL << mn->mnctr_mode_shift;
	}

	return val;
}
