reconfigure (xlator_t *this, dict_t *options)
{
	struct mdc_conf *conf = NULL;

	conf = this->private;

	GF_OPTION_RECONF ("timeout", conf->timeout, options, int32, out);
out:
	return 0;
}
