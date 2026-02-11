send_board(int extra_move) {

   char fen[256];
   int start, end;
   board_t board[1];
   int pos;
   int move;
   char string[256];

   ASSERT(extra_move==MoveNone||move_is_ok(extra_move));

   ASSERT(!Uci->searching);


   game_get_board(Game,Uci->board);
   if (extra_move != MoveNone) move_do(Uci->board,extra_move);

   board_to_fen(Uci->board,fen,256);
   my_log("POLYGLOT FEN %s\n",fen);

   ASSERT(board_can_play(Uci->board));


   start = 0;
   end = game_pos(Game);
   ASSERT(end>=start);


   game_get_board(Game,board,start);
   board_to_fen(board,string,256);

   engine_send_queue(Engine,"position");

   if (my_string_equal(string,StartFen)) {
      engine_send_queue(Engine," startpos");
   } else {
      engine_send_queue(Engine," fen %s",string);
   }


   if (end > start || extra_move != MoveNone) engine_send_queue(Engine," moves");

   for (pos = start; pos < end; pos++) {

      move = game_move(Game,pos);

      move_to_can(move,board,string,256);
      engine_send_queue(Engine," %s",string);

      move_do(board,move);
   }

   if (extra_move != MoveNone) {
      move_to_can(extra_move,board,string,256);
      engine_send_queue(Engine," %s",string);
   }


   engine_send(Engine,"");
}
