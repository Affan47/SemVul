put_raw_data(res_t *res, raw_data_t *raw, int offset)
{
	unsigned int wsize = raw->size - offset;
	if(res->allocsize - res->size < wsize)
		grow_res(res, wsize);
	memcpy(&(res->data[res->size]), raw->data + offset, wsize);
	res->size += wsize;
}
