xml_parse_object_image (xmlNodePtr  node,
			glLabel    *label)
{
	GObject      *object;
	gdouble       x, y;
	gdouble       w, h;
	gchar        *string;
	glTextNode   *filename;

	gl_debug (DEBUG_XML, "START");

	object = gl_label_image_new (label, FALSE);


	x = lgl_xml_get_prop_length (node, "x", 0.0);
	y = lgl_xml_get_prop_length (node, "y", 0.0);
	gl_label_object_set_position (GL_LABEL_OBJECT(object), x, y, FALSE);


	string = lgl_xml_get_prop_string (node, "src", NULL);
	if ( string ) {
		filename = g_new0 (glTextNode, 1);
		filename->field_flag = FALSE;
		filename->data = g_strdup ((gchar *)string);
		gl_label_image_set_filename (GL_LABEL_IMAGE(object), filename, FALSE);
		gl_text_node_free (&filename);
		xmlFree (string);
	} else {
		string = lgl_xml_get_prop_string (node, "field", NULL);
		if ( string ) {
			filename = g_new0 (glTextNode, 1);
			filename->field_flag = TRUE;
			filename->data = g_strdup ((gchar *)string);
			gl_label_image_set_filename (GL_LABEL_IMAGE(object), filename, FALSE);
			gl_text_node_free (&filename);
			xmlFree (string);
		} else {
			g_message ("Missing Object-image src or field attr");
		}
	}


	w = lgl_xml_get_prop_length (node, "w", 0);
	h = lgl_xml_get_prop_length (node, "h", 0);
	gl_label_object_set_size (GL_LABEL_OBJECT(object), w, h, FALSE);


	xml_parse_affine_attrs (node, GL_LABEL_OBJECT(object));


	xml_parse_shadow_attrs (node, GL_LABEL_OBJECT(object));

	gl_debug (DEBUG_XML, "END");
}
