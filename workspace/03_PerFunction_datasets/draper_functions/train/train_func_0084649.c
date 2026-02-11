xmmsv_dict_iter_set (xmmsv_dict_iter_t *it, xmmsv_t *val)
{
	unsigned int orig;
	int ret;

	x_return_val_if_fail (xmmsv_dict_iter_valid (it), 0);


	orig = it->lit->position;

	xmmsv_list_iter_next (it->lit);
	xmmsv_list_iter_remove (it->lit);
	ret = xmmsv_list_iter_insert (it->lit, val);


	it->lit->position = orig;

	return ret;
}
