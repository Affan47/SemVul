multi_pinfo_maybe_reload_pic(np_bitmap *b)
{

	if(b->bitmap >= 0){
		return;
	}


	if(!(Net_player->p_info.options.flags & MLO_FLAG_ACCEPT_PIX) || !(Netgame.options.flags & MSO_FLAG_ACCEPT_PIX)){
		return;
	}


	if(strlen(b->filename) <= 0){
		return;
	}


	b->bitmap = bm_load_duplicate(b->filename);
}
