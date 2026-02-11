multi_pinfo_popup(net_player *np)
{

	if(Multi_pinfo_popup_running){
		return;
	}


	Assert(np != NULL);


	gamesnd_play_iface(SND_POPUP_APPEAR);


	multi_pinfo_popup_init(np);


	Multi_pinfo_popup_running = 1;


	multi_pinfo_popup_do();


	multi_pinfo_popup_close();


	gamesnd_play_iface(SND_POPUP_DISAPPEAR);
}
