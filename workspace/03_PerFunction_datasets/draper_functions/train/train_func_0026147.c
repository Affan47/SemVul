bacon_video_osd_actor_hide (BaconVideoOsdActor *osd)
{
	g_return_if_fail (BACON_IS_VIDEO_OSD_ACTOR (osd));

	clutter_actor_hide (CLUTTER_ACTOR (osd));


	osd->priv->fade_out_alpha = 1.0;
	osd->priv->fade_timeout_id = 0;
}
