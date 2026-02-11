do_set_task(GttTask *tsk, PropTaskDlg *dlg)
{
	GttBillStatus status;
	GttBillable able;
	GttBillRate rate;
	char buff[132];

	if (!tsk)
	{
		dlg->task = NULL;
		gtk_entry_set_text(dlg->memo, "");
		xxxgtk_textview_set_text(dlg->notes, "");
		gtk_entry_set_text(dlg->unit, "0.0");
		return;
	}


	dlg->task = tsk;
	TSK_SETUP (dlg);

	gtk_entry_set_text(dlg->memo, gtt_task_get_memo(tsk));
	xxxgtk_textview_set_text(dlg->notes, gtt_task_get_notes (tsk));

	g_snprintf (buff, 132, "%g", ((double) gtt_task_get_bill_unit(tsk))/60.0);
	gtk_entry_set_text(dlg->unit, buff);

	status = gtt_task_get_billstatus (tsk);
	if (GTT_HOLD == status) gtk_option_menu_set_history (dlg->billstatus, 0);
	else if (GTT_BILL == status) gtk_option_menu_set_history (dlg->billstatus, 1);
	else if (GTT_PAID == status) gtk_option_menu_set_history (dlg->billstatus, 2);

	able = gtt_task_get_billable (tsk);
	if (GTT_BILLABLE == able) gtk_option_menu_set_history (dlg->billable, 0);
	else if (GTT_NOT_BILLABLE == able) gtk_option_menu_set_history (dlg->billable, 1);
	else if (GTT_NO_CHARGE == able) gtk_option_menu_set_history (dlg->billable, 2);

	rate = gtt_task_get_billrate (tsk);
	if (GTT_REGULAR == rate) gtk_option_menu_set_history (dlg->billrate, 0);
	else if (GTT_OVERTIME == rate) gtk_option_menu_set_history (dlg->billrate, 1);
	else if (GTT_OVEROVER == rate) gtk_option_menu_set_history (dlg->billrate, 2);
	else if (GTT_FLAT_FEE == rate) gtk_option_menu_set_history (dlg->billrate, 3);

	dlg->ignore_events = FALSE;
}
