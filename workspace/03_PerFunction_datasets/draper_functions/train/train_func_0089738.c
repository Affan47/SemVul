bacon_video_osd_actor_show_and_fade (BaconVideoOsdActor *osd)
{
	g_return_if_fail (BACON_IS_VIDEO_OSD_ACTOR (osd));

	remove_hide_timeout (osd);
	clutter_actor_set_opacity (CLUTTER_ACTOR (osd), 0xff);
	clutter_actor_show (CLUTTER_ACTOR (osd));
	add_hide_timeout (osd);
}
