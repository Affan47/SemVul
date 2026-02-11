destroy_queue(void *obj)
{
	struct call_queue *q = obj;
	int i;

	free_members(q, 1);
	ast_string_field_free_memory(q);
	for (i = 0; i < MAX_PERIODIC_ANNOUNCEMENTS; i++) {
		if (q->sound_periodicannounce[i]) {
			free(q->sound_periodicannounce[i]);
		}
	}
	ao2_ref(q->members, -1);
}
