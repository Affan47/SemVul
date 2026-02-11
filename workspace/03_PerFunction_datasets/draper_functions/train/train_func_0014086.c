lt_iter_init(lt_iter_tmpl_t *tmpl)
{
	lt_iter_t *retval;

	lt_return_val_if_fail (tmpl != NULL, NULL);
	lt_return_val_if_fail (tmpl->magic_code == MAGIC_CODE, NULL);
	lt_return_val_if_fail (tmpl->init != NULL, NULL);

	retval = tmpl->init(tmpl);
	if (retval)
		retval->target = tmpl;

	return retval;
}
