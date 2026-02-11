count_named(private_stroke_counter_t *this,
						ike_sa_t *ike_sa, stroke_counter_type_t type)
{
	entry_t *entry;
	char *name;

	name = get_ike_sa_name(ike_sa);
	if (name)
	{
		entry = this->conns->get(this->conns, name);
		if (!entry)
		{
			INIT(entry,
				.name = strdup(name),
			);
			this->conns->put(this->conns, entry->name, entry);
		}
		entry->counter[type]++;
	}
}
