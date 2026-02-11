dhcp_group_signal_handler (omapi_object_t *h,
					const char *name, va_list ap)
{
	struct group_object *group;
	isc_result_t status;
	int updatep = 0;

	if (h -> type != dhcp_type_group)
		return DHCP_R_INVALIDARG;
	group = (struct group_object *)h;

	if (!strcmp (name, "updated")) {


		if (!group -> group)
			return DHCP_R_INVALIDARG;


		if (!group -> name) {
			char hnbuf [64];
			sprintf (hnbuf, "ng%08lx%08lx",
				 (unsigned long)cur_time,
				 (unsigned long)group);
			group -> name = dmalloc (strlen (hnbuf) + 1, MDL);
			if (!group -> name)
				return ISC_R_NOMEMORY;
			strcpy (group -> name, hnbuf);
		}

		supersede_group (group, 1);
		updatep = 1;
	}


	if (h -> inner && h -> inner -> type -> get_value) {
		status = ((*(h -> inner -> type -> signal_handler))
			  (h -> inner, name, ap));
		if (status == ISC_R_SUCCESS)
			return status;
	}
	if (updatep)
		return ISC_R_SUCCESS;
	return ISC_R_NOTFOUND;
}
