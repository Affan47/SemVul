release_mem_region_adjustable(struct resource *parent,
			resource_size_t start, resource_size_t size)
{
	struct resource **p;
	struct resource *res;
	struct resource *new_res;
	resource_size_t end;
	int ret = -EINVAL;

	end = start + size - 1;
	if ((start < parent->start) || (end > parent->end))
		return ret;


	new_res = alloc_resource(GFP_KERNEL);

	p = &parent->child;
	write_lock(&resource_lock);

	while ((res = *p)) {
		if (res->start >= end)
			break;


		if (res->start > start || res->end < end) {
			p = &res->sibling;
			continue;
		}

		if (!(res->flags & IORESOURCE_MEM))
			break;

		if (!(res->flags & IORESOURCE_BUSY)) {
			p = &res->child;
			continue;
		}


		if (res->start == start && res->end == end) {

			*p = res->sibling;
			free_resource(res);
			ret = 0;
		} else if (res->start == start && res->end != end) {

			ret = __adjust_resource(res, end + 1,
						res->end - end);
		} else if (res->start != start && res->end == end) {

			ret = __adjust_resource(res, res->start,
						start - res->start);
		} else {

			if (!new_res) {
				ret = -ENOMEM;
				break;
			}
			new_res->name = res->name;
			new_res->start = end + 1;
			new_res->end = res->end;
			new_res->flags = res->flags;
			new_res->parent = res->parent;
			new_res->sibling = res->sibling;
			new_res->child = NULL;

			ret = __adjust_resource(res, res->start,
						start - res->start);
			if (ret)
				break;
			res->sibling = new_res;
			new_res = NULL;
		}

		break;
	}

	write_unlock(&resource_lock);
	free_resource(new_res);
	return ret;
}
