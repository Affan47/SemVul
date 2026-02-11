allocate_topic(struct Channel *chptr)
{
	void *ptr;

	if(chptr == NULL)
		return;

	ptr = rb_bh_alloc(topic_heap);


	chptr->topic = ptr;
	chptr->topic_info = (char *) ptr + TOPICLEN + 1;
	*chptr->topic = '\0';
	*chptr->topic_info = '\0';
}
