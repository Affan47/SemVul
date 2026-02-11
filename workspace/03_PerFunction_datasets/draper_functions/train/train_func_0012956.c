conf_set_modules_module(confentry_t * entry, conf_t * conf, struct conf_items *item)
{
#ifndef STATIC_MODULES
	char *m_bn;

	m_bn = rb_basename(entry->string);

	if(findmodule_byname(m_bn) != -1)
		return;

	load_one_module(entry->string, 0);

	rb_free(m_bn);
#else
	conf_report_error
		("Ignoring modules::module at %s:%d -- loadable module support not present.",
		 entry->filename, entry->line);
#endif


}
