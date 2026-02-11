resolve_delta(struct object_entry *delta_obj,
			  struct base_data *base, struct base_data *result)
{
	void *base_data, *delta_data;

	delta_obj->real_type = base->obj->real_type;
	delta_obj->delta_depth = base->obj->delta_depth + 1;
	if (deepest_delta < delta_obj->delta_depth)
		deepest_delta = delta_obj->delta_depth;
	delta_obj->base_object_no = base->obj - objects;
	delta_data = get_data_from_pack(delta_obj);
	base_data = get_base_data(base);
	result->obj = delta_obj;
	result->data = patch_delta(base_data, base->size,
				   delta_data, delta_obj->size, &result->size);
	free(delta_data);
	if (!result->data)
		bad_object(delta_obj->idx.offset, "failed to apply delta");
	sha1_object(result->data, result->size, delta_obj->real_type,
		    delta_obj->idx.sha1);
	nr_resolved_deltas++;
}
