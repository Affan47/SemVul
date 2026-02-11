cavan_xml_attribute_set(struct cavan_xml_attribute **head, const char *name, const char *value, int flags)
{
	struct cavan_xml_attribute *attr;

	attr = cavan_xml_attribute_find(*head, name);
	if (attr)
	{
		return cavan_xml_attribute_set_value(attr, value, flags);
	}

	attr = cavan_xml_attribute_alloc(name, value, flags);
	if (attr == NULL)
	{
		return false;
	}

	attr->next = *head;
	*head = attr;

	return true;
}
