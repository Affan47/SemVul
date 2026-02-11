debrief_multi_server_stuff()
{
	debriefing *debriefp;

	int stage_active[MAX_TVT_TEAMS][MAX_DEBRIEF_STAGES], *stages[MAX_TVT_TEAMS];
	int i, j, num_stages, stage_count[MAX_TVT_TEAMS];

	memset( stage_active, 0, sizeof(stage_active) );

	for (i=0; i<Num_teams; i++) {
		debriefp = &Debriefings[i];
		num_stages = 0;
		stages[i] = stage_active[i];
		for (j=0; j<debriefp->num_stages; j++) {
			if ( eval_sexp(debriefp->stages[j].formula) ) {
				stage_active[i][num_stages] = j;
				num_stages++;
			}
		}

		stage_count[i] = num_stages;
	}


	if (Netgame.campaign_mode == MP_CAMPAIGN) {
		multi_campaign_eval_debrief();
	}


	send_debrief_info( stage_count, stages );
}
