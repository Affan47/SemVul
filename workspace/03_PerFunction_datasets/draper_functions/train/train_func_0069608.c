selection_changed_cb (glLabel        *label,
		      glObjectEditor *editor)
{
        glLabelObject *object;

	gl_debug (DEBUG_EDITOR, "START");

	g_return_if_fail (label && GL_IS_LABEL (label));
	g_return_if_fail (editor && GL_IS_OBJECT_EDITOR (editor));

	if (!gl_label_is_selection_atomic (label))
        {
                set_object (editor, NULL);
	}
        else
        {
                object = gl_label_get_1st_selected_object (label);
                set_object (editor, object);
	}

	gl_debug (DEBUG_EDITOR, "END");
}
