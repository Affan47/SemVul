cc_generic_agent_stop_offer_timer(struct ast_cc_agent *agent)
{
	struct cc_generic_agent_pvt *generic_pvt = agent->private_data;

	if (generic_pvt->offer_timer_id != -1) {
		if (!ast_sched_del(cc_sched_context, generic_pvt->offer_timer_id)) {
			cc_unref(agent, "Remove scheduler's reference to the agent");
		}
		generic_pvt->offer_timer_id = -1;
	}
	return 0;
}
