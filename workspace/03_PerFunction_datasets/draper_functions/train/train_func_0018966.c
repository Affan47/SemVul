fetchhead_ref_cb(const char *name, const char *url,
	const git_oid *oid, unsigned int is_merge, void *payload)
{
	fetchhead_ref_cb_data *cb_data = payload;
	git_fetchhead_ref *expected;

	cl_assert(payload);

	expected = git_vector_get(cb_data->fetchhead_vector, cb_data->idx);

	cl_assert(git_oid_cmp(&expected->oid, oid) == 0);
	cl_assert(expected->is_merge == is_merge);

	if (expected->ref_name)
		cl_assert_equal_s(expected->ref_name, name);
	else
		cl_assert(name == NULL);

	if (expected->remote_url)
		cl_assert_equal_s(expected->remote_url, url);
	else
		cl_assert(url == NULL);

	cb_data->idx++;

	return 0;
}
