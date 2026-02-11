exchange_free_aca_list(struct exchange *exchange)
{
	struct certreq_aca *aca;

	for (aca = TAILQ_FIRST(&exchange->aca_list); aca;
	    aca = TAILQ_FIRST(&exchange->aca_list)) {
		if (aca->data) {
			if (aca->handler)
				aca->handler->free_aca(aca->data);
			free(aca->data);
		}
		TAILQ_REMOVE(&exchange->aca_list, aca, link);
		free(aca);
	}
}
