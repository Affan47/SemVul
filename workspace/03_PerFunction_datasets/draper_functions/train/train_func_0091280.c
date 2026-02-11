xml_create_objects (xmlNodePtr  parent,
		    xmlNsPtr    ns,
		    glLabel    *label)
{
	xmlNodePtr     node;
        gboolean       rotate_flag;
        const GList   *object_list;
	GList         *p;
	glLabelObject *object;

	gl_debug (DEBUG_XML, "START");

        rotate_flag = gl_label_get_rotate_flag (label);
        object_list = gl_label_get_object_list (label);

	node = xmlNewChild (parent, ns, (xmlChar *)"Objects", NULL);
	lgl_xml_set_prop_string (node, "id", "0");
	lgl_xml_set_prop_boolean (node, "rotate", rotate_flag);

	for (p = (GList *)object_list; p != NULL; p = p->next) {

		object = GL_LABEL_OBJECT(p->data);

		if ( GL_IS_LABEL_TEXT(object) ) {
			xml_create_object_text (node, ns, object);
		} else if ( GL_IS_LABEL_BOX(object) ) {
			xml_create_object_box (node, ns, object);
		} else if ( GL_IS_LABEL_ELLIPSE(object) ) {
			xml_create_object_ellipse (node, ns, object);
		} else if ( GL_IS_LABEL_LINE(object) ) {
			xml_create_object_line (node, ns, object);
		} else if ( GL_IS_LABEL_IMAGE(object) ) {
			xml_create_object_image (node, ns, object);
		} else if ( GL_IS_LABEL_BARCODE(object) ) {
			xml_create_object_barcode (node, ns, object);
		} else {
			g_message ("Unknown label object");
		}

	}

	gl_debug (DEBUG_XML, "END");
}
