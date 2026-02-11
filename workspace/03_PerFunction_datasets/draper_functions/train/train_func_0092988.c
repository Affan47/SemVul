_insert_area(struct dm_list *head, struct pv_area *a, unsigned reduced)
{
	struct pv_area *pva;
	uint32_t count = reduced ? a->unreserved : a->count;

	dm_list_iterate_items(pva, head)
		if (count > pva->count)
			break;

	dm_list_add(&pva->list, &a->list);
	a->map->pe_count += a->count;
}
