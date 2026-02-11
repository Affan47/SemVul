level_page_in()
{

	game_busy( NOX("*** paging in ships ***") );
	ship_page_in();

	game_busy( NOX("*** paging in weapons ***") );
	weapons_page_in();
	game_busy( NOX("*** paging in various effects ***") );
	fireballs_page_in();
	particle_page_in();
	debris_page_in();
	hud_page_in();
	stars_page_in();
	shockwave_page_in();
	shield_hit_page_in();
	asteroid_page_in();
	neb2_page_in();
	mflash_page_in(false);


	if (game_using_low_mem() == false) {
		message_pagein_mission_messages();
	}

	if(!(Game_mode & GM_STANDALONE_SERVER)){
		model_page_in_stop();
		bm_page_in_stop();
	}

	mprintf(( "Ending level bitmap paging...\n" ));

}
