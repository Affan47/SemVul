build_dialplan_useage_map(struct parking_dp_map *usage_map, int complain)
{
	int status = 0;
	struct ao2_iterator iter;
	struct ast_parkinglot *curlot;


	iter = ao2_iterator_init(parkinglots, 0);
	for (; (curlot = ao2_iterator_next(&iter)); ao2_ref(curlot, -1)) {

		if (dialplan_usage_add_parkinglot(usage_map, curlot, complain)) {
			ao2_ref(curlot, -1);
			status = -1;
			break;
		}
	}
	ao2_iterator_destroy(&iter);

	return status;
}
