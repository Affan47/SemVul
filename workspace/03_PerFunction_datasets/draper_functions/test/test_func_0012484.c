print_one(private_stroke_counter_t *this, FILE *out, char *name)
{
	u_int64_t counter[COUNTER_MAX];
	entry_t *entry;
	int i;

	this->lock->lock(this->lock);
	entry = this->conns->get(this->conns, name);
	if (entry)
	{
		for (i = 0; i < countof(this->counter); i++)
		{
			counter[i] = entry->counter[i];
		}
	}
	this->lock->unlock(this->lock);

	if (entry)
	{
		fprintf(out, "\nList of IKE counters for '%s':\n\n", name);
		for (i = 0; i < countof(this->counter); i++)
		{
			print_counter(out, i, counter[i]);
		}
	}
	else
	{
		fprintf(out, "No IKE counters found for '%s'\n", name);
	}
}
