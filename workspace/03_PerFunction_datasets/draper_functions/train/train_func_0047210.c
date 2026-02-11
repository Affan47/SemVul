fincalc_dialog_destroy(GtkObject *object, gpointer data)
{
    FinCalcDialog *fcd = data;

    if (fcd == NULL)
        return;

    gnc_unregister_gui_component_by_data (DIALOG_FINCALC_CM_CLASS, fcd);

    g_free(fcd);
}
