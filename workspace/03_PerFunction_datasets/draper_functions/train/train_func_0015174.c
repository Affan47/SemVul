get_post_cached(struct svc_req * req)
{
    if (!st_cache_valid)
	return error_attr;

    return get_post_buf(st_cache, req);
}
