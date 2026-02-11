buildin_getusersname(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct map_session_data *pl_sd = NULL;
	int i=0,disp_num=1;

	nullpo_retr(0, sd);

	for (i=0;i<fd_max;i++) {
		if(session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) && pl_sd->state.auth){
			if( !(battle_config.hide_GM_session && pc_isGM(pl_sd)) ){
				if((disp_num++)%10==0)
					clif_scriptnext(sd,st->oid);
				clif_scriptmes(sd,st->oid,pl_sd->status.name);
			}
		}
	}
	return 0;
}
