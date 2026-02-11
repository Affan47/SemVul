canRender()
{
	if (hud_disabled() && !hud_disabled_except_messages()) {
		return false;
	}

	if ( !(Game_detail_flags & DETAIL_FLAG_HUD) ) {
		return false;
	}

	if ((Viewer_mode & disabled_views)) {
		return false;
	}

	if(pop_up) {
		if(!popUpActive()) {
			return false;
		}
	}

	return true;
}
