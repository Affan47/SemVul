notgst_element_get_toplevel (GstElement * element)
{
	g_return_val_if_fail (element != NULL, NULL);
	g_return_val_if_fail (GST_IS_ELEMENT (element), NULL);

	do {
		GstElement *parent;

		parent = (GstElement *) gst_element_get_parent (element);

		if (parent == NULL)
			break;

		gst_object_unref (parent);
		element = parent;
	} while (1);

	return element;
}
