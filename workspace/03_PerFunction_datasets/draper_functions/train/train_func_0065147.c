update_fonts (UmEditableButton *button)
{
        PangoAttrList *attrs;
        PangoAttribute *attr;
        GtkWidget *label;

        UmEditableButtonPrivate *priv = button->priv;

        attrs = pango_attr_list_new ();
        if (priv->scale_set) {
                attr = pango_attr_scale_new (priv->scale);
                pango_attr_list_insert (attrs, attr);
        }
        if (priv->weight_set) {
                attr = pango_attr_weight_new (priv->weight);
                pango_attr_list_insert (attrs, attr);
        }

        gtk_label_set_attributes (priv->label, attrs);

        label = gtk_bin_get_child (GTK_BIN (priv->button));
        gtk_label_set_attributes (GTK_LABEL (label), attrs);

        pango_attr_list_unref (attrs);
}
