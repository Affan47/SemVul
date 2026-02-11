sort_reservations_dec(void *v1, void *v2)
{
	int diff = 0;
	slurmdb_reservation_rec_t *resv_a;
	slurmdb_reservation_rec_t *resv_b;

	resv_a = *(slurmdb_reservation_rec_t **)v1;
	resv_b = *(slurmdb_reservation_rec_t **)v2;

	if (!resv_a->cluster || !resv_b->cluster)
		return 0;

	diff = strcmp(resv_a->cluster, resv_b->cluster);

	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;

	if (!resv_a->name || !resv_b->name)
		return 0;

	diff = strcmp(resv_a->name, resv_b->name);

	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;

	if (resv_a->time_start < resv_b->time_start)
		return 1;
	else if (resv_a->time_start > resv_b->time_start)
		return -1;

	return 0;
}
