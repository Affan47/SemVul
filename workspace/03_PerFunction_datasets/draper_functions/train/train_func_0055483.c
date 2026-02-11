neb2_page_in()
{
	int idx;


	if ( (The_mission.flags & MISSION_FLAG_FULLNEB) || Nebula_sexp_used ) {
		for (idx = 0; idx < Neb2_poof_count; idx++) {
			if ( (Neb2_poofs[idx] >= 0) && (Neb2_poof_flags & (1<<idx)) ) {
				bm_page_in_texture(Neb2_poofs[idx]);
			}
		}
	}
}
