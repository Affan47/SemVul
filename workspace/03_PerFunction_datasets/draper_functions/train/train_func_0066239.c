node_dht_would_flow_control(size_t additional)
{
	if (
		dht_node && dht_node->outq &&
		mq_would_flow_control(dht_node->outq, additional)
	)
		return TRUE;

	if (
		dht6_node && dht6_node->outq &&
		mq_would_flow_control(dht6_node->outq, additional)
	)
		return TRUE;

	return FALSE;
}
