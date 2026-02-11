gl_label_barcode_finalize (GObject *object)
{
        glLabelBarcode *lbc = GL_LABEL_BARCODE (object);

        g_return_if_fail (object && GL_IS_LABEL_BARCODE (object));

        gl_text_node_free (&lbc->priv->text_node);
        gl_label_barcode_style_free (lbc->priv->style);
        gl_color_node_free (&(lbc->priv->color_node));
        lgl_barcode_free (lbc->priv->display_gbc);
        g_free (lbc->priv);

        G_OBJECT_CLASS (gl_label_barcode_parent_class)->finalize (object);
}
