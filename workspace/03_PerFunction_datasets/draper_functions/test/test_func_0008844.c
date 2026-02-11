snbep_pcu_hw_config(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct hw_perf_event_extra *reg1 = &hwc->extra_reg;
	int ev_sel = hwc->config & SNBEP_PMON_CTL_EV_SEL_MASK;

	if (ev_sel >= 0xb && ev_sel <= 0xe) {
		reg1->reg = SNBEP_PCU_MSR_PMON_BOX_FILTER;
		reg1->idx = ev_sel - 0xb;
		reg1->config = event->attr.config1 & (0xff << (reg1->idx * 8));
	}
	return 0;
}
