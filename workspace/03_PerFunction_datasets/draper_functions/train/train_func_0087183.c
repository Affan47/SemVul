e_vcard_attribute_copy (EVCardAttribute *attr)
{
	EVCardAttribute *a;
	GList *p;

	g_return_val_if_fail (attr != NULL, NULL);

	a = e_vcard_attribute_new (attr->group, attr->name);

	for (p = attr->values; p; p = p->next)
		e_vcard_attribute_add_value (a, p->data);

	for (p = attr->params; p; p = p->next)
		e_vcard_attribute_add_param (a, e_vcard_attribute_param_copy (p->data));

	return a;
}
