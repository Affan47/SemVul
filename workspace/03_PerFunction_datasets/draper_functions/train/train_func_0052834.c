action_replay_ciaread (void)
{
	if (armodel < 2)
		return;
	if (action_replay_flag != ACTION_REPLAY_IDLE)
		return;
	if (action_replay_flag == ACTION_REPLAY_INACTIVE)
		return;
	if (armode < 2)

		return;
	if (m68k_getpc () >= 0x200)
		return;
	action_replay_flag = ACTION_REPLAY_ACTIVATE;
	set_special (SPCFLAG_ACTION_REPLAY);
}
