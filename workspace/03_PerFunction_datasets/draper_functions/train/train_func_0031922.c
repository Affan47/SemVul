wb_domain_writeout_inc(struct wb_domain *dom,
				   struct fprop_local_percpu *completions,
				   unsigned int max_prop_frac)
{
	__fprop_inc_percpu_max(&dom->completions, completions,
			       max_prop_frac);

	if (!unlikely(dom->period_time)) {


		dom->period_time = wp_next_time(jiffies);
		mod_timer(&dom->period_timer, dom->period_time);
	}
}
