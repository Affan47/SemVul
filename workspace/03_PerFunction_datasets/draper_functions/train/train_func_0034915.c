gl_label_object_set_shadow_state (glLabelObject     *object,
				  gboolean           state,
                                  gboolean           checkpoint)
{
	gl_debug (DEBUG_LABEL, "START");

	g_return_if_fail (object && GL_IS_LABEL_OBJECT (object));

	if (object->priv->shadow_state != state)
	{
                if ( checkpoint )
                {
                        gl_label_checkpoint (object->priv->parent, _("Shadow state"));
                }

		object->priv->shadow_state = state;

		gl_label_object_emit_changed (object);
	}

	gl_debug (DEBUG_LABEL, "END");
}
