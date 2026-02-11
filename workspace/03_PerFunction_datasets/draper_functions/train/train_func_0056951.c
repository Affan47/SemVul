game_goto(game_t * game, int pos) {

   int i;

   ASSERT(game!=NULL);
   ASSERT(pos>=0&&pos<=game->size);

   if (pos < game->pos) {
      board_copy(game->board,game->start_board);
      game->pos = 0;
   }

   for (i = game->pos; i < pos; i++) move_do(game->board,game->move[i]);
   ASSERT(i==pos);

   game->pos = pos;

   game_update(game);
}
