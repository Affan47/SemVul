sh_tmu_clocksource_disable(struct clocksource *cs)
{
	struct sh_tmu_channel *ch = cs_to_sh_tmu(cs);

	if (WARN_ON(!ch->cs_enabled))
		return;

	sh_tmu_disable(ch);
	ch->cs_enabled = false;
}
