destroy_values()
{
	for (int i = 0; i < NUM_BUCKETS; i++) {
		struct linked_list *ptr = buckets[i];
		while (ptr) {

			if (curves)
				delete (Curve *)(ptr->obj);
			else
				free(ptr->obj);
			ptr->obj = NULL;
			ptr = ptr->next;
		}
	}
}
