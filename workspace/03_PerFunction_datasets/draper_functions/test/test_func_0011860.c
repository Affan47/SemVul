cstate_src_find(cstate_ty *cstate_data, string_ty *file_name)
{
    size_t          j;

    if (!cstate_data)
	return 0;
    if (!cstate_data->src)
	return 0;
    for (j = 0; j < cstate_data->src->length; ++j)
    {
	cstate_src_ty   *src;

	src = cstate_data->src->list[j];
	if (src && src->file_name && str_equal(src->file_name, file_name))
	    return src;
    }
    return 0;
}
