ext_got_typing(MsnConnection *mc, MsnBuddy *buddy)
{
	eb_local_account *ela = (eb_local_account *)mc->account->ext_data;
	eb_account *ea = find_account_with_ela(buddy->passport, ela);

	if (ea != NULL && iGetLocalPref("do_typing_notify"))
		eb_update_status(ea, _("typing..."));
}
