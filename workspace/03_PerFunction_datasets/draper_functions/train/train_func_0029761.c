de_media_interrupt (struct de_private *de, u32 status)
{
	if (status & LinkPass) {

		if ((de->media_type == DE_MEDIA_AUI ||
		     de->media_type == DE_MEDIA_BNC) &&
		    (de->media_lock ||
		     !de_ok_to_advertise(de, DE_MEDIA_TP_AUTO)))
			return;

		if ((de->media_type == DE_MEDIA_AUI ||
		     de->media_type == DE_MEDIA_BNC)) {
			de->media_type = DE_MEDIA_TP_AUTO;
			de_stop_rxtx(de);
			de_set_media(de);
			de_start_rxtx(de);
		}
		de_link_up(de);
		mod_timer(&de->media_timer, jiffies + DE_TIMER_LINK);
		return;
	}

	BUG_ON(!(status & LinkFail));

	if (netif_carrier_ok(de->dev) && de->media_type != DE_MEDIA_AUI &&
	    de->media_type != DE_MEDIA_BNC) {
		de_link_down(de);
		mod_timer(&de->media_timer, jiffies + DE_TIMER_NO_LINK);
	}
}
