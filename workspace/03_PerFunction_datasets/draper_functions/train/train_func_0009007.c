key_reservation_lookup (CamelObjectBag *bag,
                        gconstpointer key)
{
	GList *iter;


	for (iter = bag->reserved; iter != NULL; iter = iter->next) {
		KeyReservation *reservation = iter->data;
		if (bag->key_equal_func (reservation->key, key))
			return reservation;
	}

	return NULL;
}
