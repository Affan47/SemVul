ay_msn_terminate_chat(eb_account *account)
{
	eb_debug(DBG_MSN, "Terminated chat for %s(%s)(%p)\n", account->handle,
		account->account_contact->nick,
		account->account_contact->conversation);
	if (account->account_contact->conversation
		&& account->account_contact->conversation->
		protocol_local_conversation_data) {
		msn_sb_disconnect(account->account_contact->conversation->
			protocol_local_conversation_data);
	}
}
