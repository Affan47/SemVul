poll_mailbox(struct mailbox_mapping *mm)
{
	char buf[1024];
	unsigned int state;

	snprintf(buf, sizeof(buf), "%s@%s", mm->mailbox, mm->context);

	state = !!ast_app_has_voicemail(mm->mailbox, NULL);

	if (state != mm->cur_state) {
		if (state)
			ast_smdi_mwi_set(mm->iface, mm->smdi);
		else
			ast_smdi_mwi_unset(mm->iface, mm->smdi);

		mm->cur_state = state;
	}
}
