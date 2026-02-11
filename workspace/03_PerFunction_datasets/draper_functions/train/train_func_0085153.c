raid_class_release(struct raid_template *r)
{
	struct raid_internal *i = to_raid_internal(r);

	BUG_ON(attribute_container_unregister(&i->r.raid_attrs.ac));

	kfree(i);
}
