__ib_get_agent_port(const struct ib_device *device, int port_num)
{
	struct ib_agent_port_private *entry;

	list_for_each_entry(entry, &ib_agent_port_list, port_list) {
		if (entry->agent[1]->device == device &&
		    entry->agent[1]->port_num == port_num)
			return entry;
	}
	return NULL;
}
