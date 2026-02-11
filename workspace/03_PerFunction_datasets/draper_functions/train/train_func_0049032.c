gl_label_delete_object (glLabel       *label,
                        glLabelObject *object)
{
	gl_debug (DEBUG_LABEL, "START");

	g_return_if_fail (label && GL_IS_LABEL (label));
	g_return_if_fail (object && GL_IS_LABEL_OBJECT (object));

        label->priv->object_list = g_list_remove (label->priv->object_list, object);

        g_signal_handlers_disconnect_by_func (G_OBJECT (object),
                                              G_CALLBACK (object_changed_cb), label);
        g_signal_handlers_disconnect_by_func (G_OBJECT (object),
                                              G_CALLBACK (object_moved_cb), label);
        g_object_unref (object);

        do_modify (label);

	gl_debug (DEBUG_LABEL, "END");
}
