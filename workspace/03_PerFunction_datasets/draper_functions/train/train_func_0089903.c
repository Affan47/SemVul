cgi_query_element_integer_value(query, name)
    CGI_Query *query;
    const char *name;
{
    CGI_Query_Element *element;

    element = query->elements;
    while (element != NULL) {
	if (strcmp(element->name, name) == 0) {
	    if (strncasecmp(element->value, "0x", 2) == 0)
		return strtol((const char *)element->value + 2, NULL, 16);
	    else
		return strtol((const char *)element->value, NULL, 10);
	}
	element = element->next;
    }

    return 0;
}
