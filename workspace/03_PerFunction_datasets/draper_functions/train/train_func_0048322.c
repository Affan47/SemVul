destroy_level(Game *game) {
	int i;

	for(i = 0; i < BLOCKS_X * BLOCKS_Y; i++)
		if(game->level->blocks[i])
			remove_block(game->level->blocks,
					game->level->blocks[i]);

	g_free(game->level->name);
	g_free(game->level->author);
	g_free(game->level->levelfile_title);
	g_free(game->level);
	game->level = NULL;
}
