free_publish(const void *key, void *value, void *data)
{
	publish_t *pb = value;
	bool *exiting = data;

	publish_check(pb);
	g_assert(key == &pb->pid);


	pb->flags |= PB_F_DONT_REMOVE;

	if (*exiting) {
		publish_free(pb);
	} else {


		if (!(pb->flags & PB_F_SUBORDINATE)) {
			publish_cancel(pb, TRUE);
		}
	}
}
