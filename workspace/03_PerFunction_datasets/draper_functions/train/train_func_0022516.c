map_socket_ctrl_panel_func(int fd,char* usage,char* user,char* status)
{
	struct socket_data *sd = session[fd];

	strcpy( usage,
		( sd->func_parse == clif_parse )? "map user" :
		( sd->func_parse == chrif_parse )? "char server" : "unknown" );

	if( sd->func_parse == clif_parse && sd->auth )
	{
		struct map_session_data *sd2 = (struct map_session_data *)sd->session_data;
		sprintf( user, "%d %d(%s)", sd2->bl.id, sd2->char_id, sd2->status.name );
	}
}
