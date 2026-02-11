buildin_recovery(struct script_state *st)
{
	struct map_session_data *sd;
	int i;

	for(i=0; i<fd_max; i++) {
		if(session[i] && (sd = (struct map_session_data *)session[i]->session_data) && sd->state.auth) {
			sd->status.hp = sd->status.max_hp;
			sd->status.sp = sd->status.max_sp;
			clif_updatestatus(sd, SP_HP);
			clif_updatestatus(sd, SP_SP);
			if(unit_isdead(&sd->bl)) {
				pc_setstand(sd);
				clif_resurrection(&sd->bl, 1);
			}
		}
	}
	return 0;
}
