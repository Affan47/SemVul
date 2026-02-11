find_pool(private_stroke_attribute_t *this, char *name)
{
	enumerator_t *enumerator;
	mem_pool_t *current, *found = NULL;

	enumerator = this->pools->create_enumerator(this->pools);
	while (enumerator->enumerate(enumerator, &current))
	{
		if (streq(name, current->get_name(current)))
		{
			found = current;
			break;
		}
	}
	enumerator->destroy(enumerator);
	return found;
}
