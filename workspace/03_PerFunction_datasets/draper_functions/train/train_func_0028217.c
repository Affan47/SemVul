define_compute_type(int which)
{
	char *id;
	avrule_t *avrule;

	if (pass == 1) {
		while ((id = queue_remove(id_queue)))
			free(id);
		while ((id = queue_remove(id_queue)))
			free(id);
		while ((id = queue_remove(id_queue)))
			free(id);
		id = queue_remove(id_queue);
		free(id);
		return 0;
	}

	if (define_compute_type_helper(which, &avrule))
		return -1;

	append_avrule(avrule);
	return 0;
}
