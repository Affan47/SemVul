help_keymenu_tweek(SCROLL_S *sparms, int handle_hidden)
{
    if(handle_hidden){
	sparms->keys.menu->keys[HLP_VIEW_HANDLE].name  = "";
	sparms->keys.menu->keys[HLP_VIEW_HANDLE].label = "";
    }
    else{
	if(!((HELP_SCROLL_S *)sparms->proc.data.p)->keys_formatted){

	    mark_keymenu_dirty();
	    sparms->keys.menu->width = 0;
	    ((HELP_SCROLL_S *)sparms->proc.data.p)->keys_formatted = 1;
	}

	sparms->keys.menu->keys[HLP_VIEW_HANDLE].name  = "V";
	sparms->keys.menu->keys[HLP_VIEW_HANDLE].label = "[" N_("View Link") "]";
    }
}
