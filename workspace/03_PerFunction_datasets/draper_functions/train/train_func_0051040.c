__copy_partition(struct fdisk_partition *o)
{
	struct fdisk_partition *n = fdisk_new_partition();

	if (!n)
		return NULL;
	memcpy(n, o, sizeof(*n));
	if (n->type)
		fdisk_ref_parttype(n->type);
	if (o->name)
		n->name = strdup(o->name);
	if (o->uuid)
		n->uuid = strdup(o->uuid);
	if (o->attrs)
		n->attrs = strdup(o->attrs);
	return n;
}
