container_resolve(container_name)
	 char           *container_name;
{
	container_name = arg_text_of(container_name);


	struct integer_type *resolved_integer;

	if ((resolved_integer = integer_resolve(container_name)) != NULL)
		return (&resolved_integer->value);
	else if (object_element_resolve(container_name))
		return (object_element_address);
	else if (!strcmp(container_name, "noun1"))
		return (&noun[0]);
	else if (!strcmp(container_name, "noun2"))
		return (&noun[1]);
	else if (!strcmp(container_name, "noun3"))
		return (&noun[2]);
	else if (!strcmp(container_name, "noun4"))
		return (&noun[3]);
	else if (!strcmp(container_name, "player"))
		return (&player);
	else if (!strcmp(container_name, "here"))
		return (&object[player]->PARENT);
	else
		return ((int *) NULL);
}
