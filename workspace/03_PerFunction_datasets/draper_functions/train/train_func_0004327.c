write_selector(state_t *s, reg_t object, selector_t selector_id, reg_t value,
	       const char *fname, int line)
{
	reg_t *address;

	if ((selector_id < 0) || (selector_id > s->selector_names_nr)) {
		SCIkwarn(SCIkWARNING, "Attempt to write to invalid selector %d of"
			 " object at "PREG" (%s L%d).\n", selector_id,
			 PRINT_REG(object), fname, line);
		return;
	}

	if (lookup_selector(s, object, selector_id, &address, NULL) != SELECTOR_VARIABLE)
		SCIkwarn(SCIkWARNING, "Selector '%s' of object at %04x could not be"
			 " written to (%s L%d)\n",
			 s->selector_names[selector_id], object, fname, line);
	else
		*address = value;

}
