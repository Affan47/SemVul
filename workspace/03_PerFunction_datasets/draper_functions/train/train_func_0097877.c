isns_create_object(isns_object_template_t *tmpl,
		const isns_attr_list_t *attrs,
		isns_object_t *parent)
{
	isns_object_t	*obj;
	unsigned int	i;


	if (parent)
		isns_assert(tmpl->iot_container == parent->ie_template);

#ifdef notdef

	if (attrs && tmpl != isns_object_template_for_key_attrs(attrs))
		return NULL;
#endif

	obj = isns_calloc(1, sizeof(*obj));

	obj->ie_users = 1;
	obj->ie_template = tmpl;
	isns_attr_list_init(&obj->ie_attrs);

	if (parent)
		isns_object_attach(obj, parent);

	if (attrs == NULL) {


		for (i = 0; i < tmpl->iot_num_keys; ++i)
			isns_attr_list_append_nil(&obj->ie_attrs,
					tmpl->iot_keys[i]);
	} else {


		isns_attr_list_copy(&obj->ie_attrs, attrs);
	}


	__isns_mark_object(obj);

	return obj;
}
