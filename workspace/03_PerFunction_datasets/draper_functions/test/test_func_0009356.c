allocate_topic(struct Channel *chptr)
{
	if(chptr == NULL)
		return;

	chptr->topic = rb_bh_alloc(topic_heap);
}
