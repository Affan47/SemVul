_lt_ext_ldml_u_destroy_data(lt_pointer_t data)
{
	lt_ext_ldml_u_data_t *d = (lt_ext_ldml_u_data_t *)data;

	if (d->attributes)
		lt_list_free(d->attributes);
	if (d->tags)
		lt_list_free(d->tags);
}
