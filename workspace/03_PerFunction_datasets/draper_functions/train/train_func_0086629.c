gnc_customer_taxincluded_changed_cb (GtkWidget *widget, gpointer data)
{
    GtkComboBox *cbox = GTK_COMBO_BOX (widget);
    CustomerWindow *cw = data;

    if (!cw) return;
    if (!cbox) return;

    cw->taxincluded = GPOINTER_TO_INT (gnc_simple_combo_get_value (cbox));
}
