attr_fe_func (const char *key, xmmsv_t *val, void *user_data)
{
	struct attr_fe_data *d = user_data;
	const char *v;
	int r;

	r = xmmsv_get_string (val, &v);
	x_return_if_fail (r)

	d->func (key, v, d->userdata);
}
