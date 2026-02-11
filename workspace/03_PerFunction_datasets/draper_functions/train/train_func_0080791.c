gl_label_barcode_get_style (glLabelBarcode *lbc)
{
        g_return_val_if_fail (lbc && GL_IS_LABEL_BARCODE (lbc), NULL);

        return gl_label_barcode_style_dup (lbc->priv->style);
}
