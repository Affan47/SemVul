groupacs_add(mygroup_t *mg, myuser_t *mu, unsigned int flags)
{
	groupacs_t *ga;

	return_val_if_fail(mg != NULL, NULL);
	return_val_if_fail(mu != NULL, NULL);

	ga = mowgli_heap_alloc(groupacs_heap);
	object_init(object(ga), NULL, (destructor_t) groupacs_des);

	ga->mg = mg;
	ga->mu = mu;
	ga->flags = flags;

	mowgli_node_add(ga, &ga->gnode, &mg->acs);
	mowgli_node_add(ga, &ga->unode, myuser_get_membership_list(mu));

	return ga;
}
