handle_attribute(private_ike_config_t *this,
							 configuration_attribute_t *ca)
{
	attribute_handler_t *handler = NULL;
	enumerator_t *enumerator;
	entry_t *entry;


	enumerator = this->requested->create_enumerator(this->requested);
	while (enumerator->enumerate(enumerator, &entry))
	{
		if (entry->type == ca->get_type(ca))
		{
			handler = entry->handler;
			this->requested->remove_at(this->requested, enumerator);
			free(entry);
			break;
		}
	}
	enumerator->destroy(enumerator);


	handler = hydra->attributes->handle(hydra->attributes,
							this->ike_sa->get_other_id(this->ike_sa), handler,
							ca->get_type(ca), ca->get_chunk(ca));
	this->ike_sa->add_configuration_attribute(this->ike_sa,
							handler, ca->get_type(ca), ca->get_chunk(ca));
}
