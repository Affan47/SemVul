get_transport_nat_ts(private_child_create_t *this,
										   bool local, linked_list_t *in)
{
	enumerator_t *enumerator;
	linked_list_t *out;
	traffic_selector_t *ts;
	host_t *ike, *first = NULL;
	u_int8_t mask;

	if (local)
	{
		ike = this->ike_sa->get_my_host(this->ike_sa);
	}
	else
	{
		ike = this->ike_sa->get_other_host(this->ike_sa);
	}

	out = linked_list_create();

	enumerator = in->create_enumerator(in);
	while (enumerator->enumerate(enumerator, &ts))
	{

		if (ts->is_host(ts, first))
		{
			if (!first)
			{
				ts->to_subnet(ts, &first, &mask);
			}
			ts = ts->clone(ts);
			ts->set_address(ts, ike);
			out->insert_last(out, ts);
		}
	}
	enumerator->destroy(enumerator);
	DESTROY_IF(first);

	return out;
}
