gl_print_op_dialog_finalize (GObject *object)
{
	glPrintOpDialog *op = GL_PRINT_OP_DIALOG (object);

	gl_debug (DEBUG_PRINT, "");

	g_return_if_fail (object != NULL);
        g_return_if_fail (GL_IS_PRINT_OP (op));
	g_return_if_fail (op->priv != NULL);

        g_object_unref (G_OBJECT(op->priv->builder));
	g_free (op->priv);

	G_OBJECT_CLASS (gl_print_op_dialog_parent_class)->finalize (object);

	g_free (op->priv);
}
