gnc_employee_window_ok_cb (GtkWidget *widget, gpointer data)
{
    EmployeeWindow *ew = data;
    gchar *string;


    if (check_entry_nonempty (ew->dialog, ew->username_entry,
                              _("You must enter a username.")))
        return;


    if (check_entry_nonempty (ew->dialog, ew->name_entry,
                              _("You must enter the employee's name.")))
        return;


    if (check_entry_nonempty (ew->dialog, ew->addr1_entry, NULL) &&
            check_entry_nonempty (ew->dialog, ew->addr2_entry, NULL) &&
            check_entry_nonempty (ew->dialog, ew->addr3_entry, NULL) &&
            check_entry_nonempty (ew->dialog, ew->addr4_entry, NULL))
    {
        const char *msg = _("You must enter an address.");
        gnc_error_dialog (ew->dialog, "%s", msg);
        return;
    }


    if (g_strcmp0 (gtk_entry_get_text (GTK_ENTRY (ew->id_entry)), "") == 0)
    {
        string = gncEmployeeNextID (ew->book);
        gtk_entry_set_text (GTK_ENTRY (ew->id_entry), string);
        g_free(string);
    }


    {
        GncEmployee *employee = ew_get_employee (ew);
        if (employee)
        {
            gnc_ui_to_employee (ew, employee);
        }
        ew->created_employee = employee;
        ew->employee_guid = *guid_null ();
    }

    gnc_close_gui_component (ew->component_id);
}
