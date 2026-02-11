gwy_sensitivity_group_get_widget_mask(GwySensitivityGroup *sensgroup,
                                      GtkWidget *widget)
{
    SensList *senslist;

    g_return_val_if_fail(GWY_IS_SENSITIVITY_GROUP(sensgroup), 0);
    g_return_val_if_fail(GTK_IS_WIDGET(widget), 0);
    senslist = gwy_sensitivity_group_get_senslist(sensgroup, G_OBJECT(widget));
    if (!senslist)
        return 0;

    return senslist->mask;
}
