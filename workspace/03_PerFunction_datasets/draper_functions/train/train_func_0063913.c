expunge_and_close_begins(int flags, char *folder)
{
    if(!(flags & EC_NO_CLOSE)){
	q_status_message1(SM_INFO, 0, 1, "Closing \"%.200s\"...", folder);
	flush_status_messages(1);
    }
}
