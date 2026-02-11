tg3_restore_clk(struct tg3 *tp)
{
	u32 val;

	switch (tg3_asic_rev(tp)) {
	case ASIC_REV_5717:
		val = tr32(TG3_CPMU_CLCK_ORIDE_ENABLE);
		tw32(TG3_CPMU_CLCK_ORIDE_ENABLE,
		     val & ~TG3_CPMU_MAC_ORIDE_ENABLE);
		break;

	case ASIC_REV_5719:
	case ASIC_REV_5720:
		val = tr32(TG3_CPMU_CLCK_ORIDE);
		tw32(TG3_CPMU_CLCK_ORIDE, val & ~CPMU_CLCK_ORIDE_MAC_ORIDE_EN);
		break;

	default:
		return;
	}
}
