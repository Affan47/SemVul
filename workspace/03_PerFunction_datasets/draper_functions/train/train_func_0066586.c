xmmsv_dict_iter_next (xmmsv_dict_iter_t *it)
{
	x_return_if_fail (it);


	xmmsv_list_iter_next (it->lit);
	xmmsv_list_iter_next (it->lit);
}
