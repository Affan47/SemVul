object_bag_unreserve (CamelObjectBag *bag,
                      gconstpointer key)
{
	KeyReservation *reservation;

	reservation = key_reservation_lookup (bag, key);
	g_return_if_fail (reservation != NULL);
	g_return_if_fail (reservation->owner == g_thread_self ());

	if (reservation->waiters > 0) {
		reservation->owner = NULL;
		g_cond_signal (&reservation->cond);
	} else
		key_reservation_free (bag, reservation);
}
