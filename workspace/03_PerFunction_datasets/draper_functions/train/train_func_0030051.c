plpgsql_ns_push(char *label)
{
	PLpgSQL_ns *new;

	if (label == NULL)
		label = "";

	new = palloc(sizeof(PLpgSQL_ns));
	memset(new, 0, sizeof(PLpgSQL_ns));
	new->upper = ns_current;
	ns_current = new;

	plpgsql_ns_additem(PLPGSQL_NSTYPE_LABEL, 0, label);
}
