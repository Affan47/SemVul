generic_agent_devstate_unsubscribe(void *data)
{
	struct ast_cc_agent *agent = data;
	struct cc_generic_agent_pvt *generic_pvt = agent->private_data;

	if (generic_pvt->sub != NULL) {
		generic_pvt->sub = ast_event_unsubscribe(generic_pvt->sub);
	}
	cc_unref(agent, "Done unsubscribing from devstate");
	return 0;
}
