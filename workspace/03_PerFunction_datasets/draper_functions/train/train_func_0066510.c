gl_label_set_selection_line_width (glLabel  *label,
				  gdouble  line_width)
{
        GList         *selection_list;
	GList         *p;
	glLabelObject *object;

	gl_debug (DEBUG_LABEL, "START");

	g_return_if_fail (label && GL_IS_LABEL (label));

        begin_selection_op (label);

        selection_list = gl_label_get_selection_list (label);

	for (p = selection_list; p != NULL; p = p->next)
        {
		object = GL_LABEL_OBJECT (p->data);
		gl_label_object_set_line_width (object, line_width, TRUE);
	}

        g_list_free (selection_list);

        end_selection_op (label);

	gl_debug (DEBUG_LABEL, "END");
}
