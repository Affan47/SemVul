find_dr(struct device *dev, dr_release_t release,
			      dr_match_t match, void *match_data)
{
	struct devres_node *node;

	list_for_each_entry_reverse(node, &dev->devres_head, entry) {
		struct devres *dr = container_of(node, struct devres, node);

		if (node->release != release)
			continue;
		if (match && !match(dev, dr->data, match_data))
			continue;
		return dr;
	}

	return NULL;
}
