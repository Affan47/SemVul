disp_nation_chat(int refreshFlag)
{
	int nationRecno = nation_filter(info.browse_nation_recno);


	if( !(sys.debug_session || nation_array[nationRecno]->nation_type == NATION_REMOTE &&
		 info.viewing_nation_recno == nation_array.player_recno ) )
	{
		return;
	}


	vga_util.d3_panel_down( REPORT_DET_X1, REPORT_DET_Y1, REPORT_DET_X2, REPORT_TALK_Y2 );

	font_san.put( REPORT_DET_X1+10, REPORT_DET_Y1+10,
					  "Please enter your chat message and press <Enter> to send." );


	if( !init_get_chat )
	{
		get_chat.init( REPORT_DET_X1+10, REPORT_DET_Y1+30, REPORT_DET_X2-10,
			info.player_chat_str, CHAT_STR_LEN, &font_san, 0, 0 );
		get_chat.clear();
		init_get_chat = 1;
	}


	int vgaUseBack = vga.use_back_buf;

	vga.use_back();
	get_chat.paint(1);

	if( !vgaUseBack )
		vga.use_front();


	int y=REPORT_TALK_Y2-70;

	for( int i=1 ; i<=MAX_CHAT_RECEIVER_TYPE ; i++, y+=22 )
	{
		if( info.chat_receiver_type == i )
			vga_util.d3_panel_down( REPORT_DET_X1+10, y, REPORT_DET_X2-10, y+20 );
		else
			vga_util.d3_panel_up( REPORT_DET_X1+10, y, REPORT_DET_X2-10, y+20 );

		font_san.center_put( REPORT_DET_X1+10, y, REPORT_DET_X2-10, y+20, chat_receiver_str_array[i-1] );
	}
}
