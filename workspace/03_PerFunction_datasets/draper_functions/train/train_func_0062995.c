change_choix_nouvel_etat ( GtkWidget *combobox, GtkWidget *label_description )
{
    gchar *description;

    switch ( gtk_combo_box_get_active ( GTK_COMBO_BOX (combobox) ) )
    {
	case 0:


	    description = _("This report displays totals for last month's transactions sorted by categories and sub-categories. You just need to select the account(s). By default, all accounts are selected.");
	    break;

	case 1:


	    description = _("This report displays totals of current month's transactions sorted by categories and sub-categories. You just need to select the account(s). By default, all accounts are selected.");
	    break;

	case 2:


	    description = _("This report displays annual budget. You just need to select the account(s). By default all accounts are selected.");
	    break;

	case 3:


	    description = _("This report is an empty one. You need to customize it entirely.");
	    break;

	case 4:


	    description = _("This report displays the cheques deposit. You just need to select the account(s). By default all accounts are selected.");
	    break;

	case 5:


	    description = _("This report displays current month's outgoings sorted by payees. You just need to select the account(s). By default all accounts are selected.");
	    break;

	case 6:


	    description = _("This report displays all the information for all transactions of all accounts for the current year. You just have to add the amount, date, payees etc. criteria thant you want. By default the transactions are clickables.");
	    break;

	default:

	    description = _("No description available");
    }

    gtk_label_set_text ( GTK_LABEL ( label_description ),
			 description );

}
