IRC_Display( int event , const char * nick , const char *message )
{
	char buffer[ IRC_RECV_BUF_SIZE * 2 ];
	char nick_copy[ IRC_MAX_NICK_LEN * 2 ];
	char message_copy[ IRC_MAX_ARG_LEN * 2 ];
	const char *fmt_string;
	qboolean has_nick;
	qboolean has_message;


	if ( IRC_QuitRequested )
		return;


	switch ( IRC_EventType( event ) ) {
		case IRC_EVT_SAY:
			has_nick = has_message = true;
			if ( IRC_EventIsSelf( event ) ) {
				fmt_string = "^2<^7%s^2> %s";
			} else if ( strstr( message , IRC_User.nick ) ) {
				fmt_string = "^3<^7%s^3> %s";
			} else {
				fmt_string = "^1<^7%s^1> %s";
			}
			break;
		case IRC_EVT_ACT:
			has_nick = has_message = true;
			if ( IRC_EventIsSelf( event ) ) {
				fmt_string = "^2* ^7%s^2 %s";
			} else if ( strstr( message , IRC_User.nick ) ) {
				fmt_string = "^3* ^7%s^3 %s";
			} else {
				fmt_string = "^1* ^7%s^1 %s";
			}
			break;
		case IRC_EVT_JOIN:
			has_message = false;
			has_nick = !IRC_EventIsSelf( event );
			if ( has_nick ) {
				fmt_string = "^5-> ^7%s^5 has entered the channel.";
			} else {
				fmt_string = "^2Joined IRC chat.";
			}
			break;
		case IRC_EVT_PART:


			has_nick = true;
			has_message = ( message[0] != 0 );
			if ( has_message ) {
				fmt_string = "^5<- ^7%s^5 has left the channel: %s.";
			} else {
				fmt_string = "^5<- ^7%s^5 has left the channel.";
			}
			break;
		case IRC_EVT_QUIT:
			has_nick = !IRC_EventIsSelf( event );
			if ( has_nick ) {
				has_message = ( message[0] != 0 );
				if ( has_message ) {
					fmt_string = "^5<- ^7%s^5 has quit: %s.";
				} else {
					fmt_string = "^5<- ^7%s^5 has quit.";
				}
			} else {
				has_message = true;
				fmt_string = "^2Quit IRC chat: %s.";
			}
			break;
		case IRC_EVT_KICK:
			has_nick = has_message = true;
			if ( IRC_EventIsSelf( event ) ) {
				fmt_string = "^2Kicked by ^7%s^2: %s.";
			} else {
				fmt_string = "^5<- ^7%s^5 has been kicked: %s.";
			}
			break;
		case IRC_EVT_NICK_CHANGE:
			has_nick = has_message = true;
			if ( IRC_EventIsSelf( event ) ) {
				fmt_string = "^2** ^7%s^2 is now known as ^7%s^2.";
			} else {
				fmt_string = "^5** ^7%s^5 is now known as ^7%s^5.";
			}
			break;
		default:
			has_nick = has_message = false;
			fmt_string = "unknown message received";
			break;
	}


	if ( has_nick )
		IRC_NeutraliseString( nick_copy , nick );
	if ( has_message )
		IRC_NeutraliseString( message_copy , message );


	if ( has_nick && has_message ) {
		sprintf( buffer , fmt_string , nick_copy , message_copy );
	} else if ( has_nick ) {
		sprintf( buffer , fmt_string , nick_copy );
	} else if ( has_message ) {
		sprintf( buffer , fmt_string , message_copy );
	} else {
		strncpy( buffer , fmt_string , IRC_RECV_BUF_SIZE * 2 - 1 );
	}
	buffer[ IRC_RECV_BUF_SIZE * 2 - 1 ] = 0;

	SCR_IRCPrintf( "^1IRC: %s", buffer );
}
