check_duplicate_property_names(struct check *c, struct node *dt,
					   struct node *node)
{
	struct property *prop, *prop2;

	for_each_property(node, prop) {
		for (prop2 = prop->next; prop2; prop2 = prop2->next) {
			if (prop2->deleted)
				continue;
			if (streq(prop->name, prop2->name))
				FAIL(c, "Duplicate property name %s in %s",
				     prop->name, node->fullpath);
		}
	}
}
