kernel_lookup_text(state_t *s, reg_t address, int index)

{
	char *seeker;
	resource_t *textres;

	if (address.segment)
		return (char *) kernel_dereference_bulk_pointer(s, address, 0);
	else {
		int textlen;
		int _index = index;
		textres = scir_find_resource(s->resmgr, sci_text, address.offset, 0);

		if (!textres) {
			SCIkwarn(SCIkERROR, "text.%03d not found\n", address);
			return NULL;
		}

		textlen = textres->size;
		seeker = (char *) textres->data;

		while (index--)
			while ((textlen--) && (*seeker++));

		if (textlen)
			return seeker;
		else {
			SCIkwarn(SCIkERROR, "Index %d out of bounds in text.%03d\n", _index, address);
			return 0;
		}

	}
}
