cmp_objects(git_rawobj *o, object_data *d)
{
	if (o->type != git_object_string2type(d->type))
		return -1;
	if (o->len != d->dlen)
		return -1;
	if ((o->len > 0) && (memcmp(o->data, d->data, o->len) != 0))
		return -1;
	return 0;
}
