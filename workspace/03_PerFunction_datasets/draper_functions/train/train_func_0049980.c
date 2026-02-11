remove_ship_status_item(net_player *p,int id)
{
	int idx;
	for(idx=id;idx<BUTTON_INFO_SAVE_COUNT-1;idx++){
		p->s_info.last_buttons[idx] = p->s_info.last_buttons[idx+1];
		p->s_info.last_buttons_id[idx] = p->s_info.last_buttons_id[idx+1];
		p->s_info.last_buttons_time[idx] = p->s_info.last_buttons_time[idx+1];
	}
}
