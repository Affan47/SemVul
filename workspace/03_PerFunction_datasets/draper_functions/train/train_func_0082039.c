gl_merge_text_finalize (GObject *object)
{
	glMergeText *merge_text = GL_MERGE_TEXT (object);

	gl_debug (DEBUG_MERGE, "START");

	g_return_if_fail (object && GL_IS_MERGE_TEXT (object));

        clear_keys (merge_text);
        g_ptr_array_free (merge_text->priv->keys, TRUE);
	g_free (merge_text->priv);

	G_OBJECT_CLASS (gl_merge_text_parent_class)->finalize (object);

	gl_debug (DEBUG_MERGE, "END");
}
