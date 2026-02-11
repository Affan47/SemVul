process_deny_packet(ubyte *data, header *hinfo)
{
	int offset,code;


	offset = HEADER_LENGTH;
	GET_INT(code);
	PACKET_SET_SIZE();


	if(popup_active()){
		return;
	}


	switch(code){
	case JOIN_DENY_JR_STATE :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You have been rejected because the game is not in an appropriate state to accept",722));
		break;
	case JOIN_DENY_JR_TRACKER_INVAL :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You have been rejected because this is a Parallax Online game and you are not a registered Parallax Online pilot",723));
		break;
	case JOIN_DENY_JR_PASSWD :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You have been rejected because this is a password protected game",724));
		break;
	case JOIN_DENY_JR_CLOSED :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You have been rejected because this is a closed game and the mission is in progress",725));
		break;
	case JOIN_DENY_JR_TEMP_CLOSED :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You have been rejected because the netgame is forming and the host has temporarily closed it",726));
		break;
	case JOIN_DENY_JR_RANK_HIGH :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You have been rejected because this is a rank limited game and your rank is too high",727));
		break;
	case JOIN_DENY_JR_RANK_LOW :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You have been rejected because this is a rank limited game and your rank is too low",728));
		break;
	case JOIN_DENY_JR_DUP :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You have been rejected because there is an identical player already in the game",729));
		break;
	case JOIN_DENY_JR_FULL :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You have been rejected because the game is full",730));
		break;
	case JOIN_DENY_JR_BANNED :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You have been rejected because you are banned from this server",731));
		break;
	case JOIN_DENY_JR_NOOBS :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You have been rejected because this game does not allow observers",732));
		break;
	case JOIN_DENY_JR_INGAME_JOIN :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You cannot join at this time since someone else is currently joining.  Try again shortly.",733));
		break;
	case JOIN_DENY_JR_BAD_VERSION :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You cannot join this game because you are running an older version of FreeSpace than the server.  Exit FreeSpace, and choose the 'Update FreeSpace' button in the FreeSpace launcher to download the latest version of FreeSpace.",734));
		break;
	case JOIN_DENY_JR_TYPE :
		popup(PF_USE_AFFIRMATIVE_ICON,1,POPUP_OK,XSTR("You cannot join a game in progress unless it is a dogfight mission.",1433));
		break;
	}


	multi_join_reset_join_stamp();
}
