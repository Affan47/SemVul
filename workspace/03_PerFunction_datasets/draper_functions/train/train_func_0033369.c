sq_to_td(struct throtl_service_queue *sq)
{
	struct throtl_grp *tg = sq_to_tg(sq);

	if (tg)
		return tg->td;
	else
		return container_of(sq, struct throtl_data, service_queue);
}
