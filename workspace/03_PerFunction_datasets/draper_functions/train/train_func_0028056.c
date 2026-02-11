gog_object_write_xml_sax (GogObject const *obj, GsfXMLOut *output, gpointer user)
{
	guint	     n;
	GParamSpec **props;
	GSList	    *ptr;

	g_return_if_fail (GOG_IS_OBJECT (obj));

	gsf_xml_out_start_element (output, "GogObject");


	if (obj->role != NULL) {
		if (strcmp (obj->role->id, GOG_BACKPLANE_NEW_ROLE_NAME) == 0)
			gsf_xml_out_add_cstr (output, "role", GOG_BACKPLANE_OLD_ROLE_NAME);
		else
			gsf_xml_out_add_cstr (output, "role", obj->role->id);
	}
	if (obj->explicitly_typed_role || obj->role == NULL)
		gsf_xml_out_add_cstr (output, "type", G_OBJECT_TYPE_NAME (obj));


	props = g_object_class_list_properties (G_OBJECT_GET_CLASS (obj), &n);
	while (n-- > 0)
		if (props[n]->flags & GO_PARAM_PERSISTENT)
			gog_object_write_property_sax (obj, props[n], output);

	g_free (props);

	if (GO_IS_PERSIST (obj))
		go_persist_sax_save (GO_PERSIST (obj), output);
	if (GOG_IS_DATASET (obj))
		gog_dataset_sax_save (GOG_DATASET (obj), output, user);


	for (ptr = obj->children; ptr != NULL ; ptr = ptr->next)
		gog_object_write_xml_sax (ptr->data, output, user);

	gsf_xml_out_end_element (output);
}
