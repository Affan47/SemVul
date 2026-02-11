chat_npckickall(struct chat_data *cd)
{
	nullpo_retr(0, cd);

	while(cd->users > 0) {
		chat_leavechat(cd->usersd[cd->users-1],0);
	}
	return 0;
}
