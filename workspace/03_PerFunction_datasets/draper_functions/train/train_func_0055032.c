SCR_Draw2D( void )
{
	if(!scr_draw2d->integer)
		return;

	CL_PickupItemStretchCrosshair();

	if (crosshair->integer)
		SCR_DrawCrosshair ();


	CL_AddPainPic();


	SCR_ExecuteLayoutString( cl.configstrings[CS_STATUSBAR] );


	if (cl.frame.playerstate.stats[STAT_LAYOUTS] & 1)
		SCR_ExecuteLayoutString( cl.layout );

	if (cl.frame.playerstate.stats[STAT_LAYOUTS] & 2)
		CL_DrawInventory ();

	SCR_DrawNet ();
	SCR_CheckDrawCenterString ();

	if(scr_drawlagometer->integer)
		SCR_DrawLagometer();

	if(cl_fps->integer)
		SCR_DrawFPS ();

	if(cl_maptime->integer)
		SCR_ShowTIME ();

	if(cl_chathud->integer)
		SCR_DrawChatHUD ();

	if(cl_clock->integer)
		SCR_DrawClock ();

	if (scr_objects)
		draw_objects();
}
