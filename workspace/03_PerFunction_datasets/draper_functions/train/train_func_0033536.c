gl_label_raise_selection_to_top (glLabel       *label)
{
        GList         *selection_list;
        GList         *p;
        glLabelObject *object;

	gl_debug (DEBUG_LABEL, "START");

        gl_label_checkpoint (label, _("Bring to front"));

        begin_selection_op (label);

        selection_list = gl_label_get_selection_list (label);

        for ( p = selection_list; p != NULL; p = p->next )
        {
                object = GL_LABEL_OBJECT (p->data);

                label->priv->object_list = g_list_remove (label->priv->object_list, object);
        }


	label->priv->object_list = g_list_concat (label->priv->object_list, selection_list);

        do_modify (label);

        end_selection_op (label);

	gl_debug (DEBUG_LABEL, "END");
}
