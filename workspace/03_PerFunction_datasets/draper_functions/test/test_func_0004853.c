search_full_init(list_t * list, board_t * board) {

   int depth, move_nb;
   int trans_move, trans_min_depth, trans_max_depth, trans_min_value, trans_max_value, trans_eval;

   ASSERT(list_is_ok(list));
   ASSERT(board_is_ok(board));


   for (depth = 0; depth < LMRDepthMax; depth++) {

      for (move_nb = 0; move_nb < ListSize; move_nb++) {

        LMRList[0][depth][move_nb] = uint8((sqrt(double(depth-1)) + sqrt(double(move_nb-1))) * 2 / 3);
        LMRList[1][depth][move_nb] = uint8( sqrt(double(depth-1)) + sqrt(double(move_nb-1)));
      }
   }


   UseAspiration = option_get_bool("Aspiration Search");
   AspirationDepth = option_get_int("Aspiration Depth");
   AspirationWindow = option_get_int("Aspiration Window");


   MoveNb = option_get_int("MultiPV");


   ThreadNb = option_get_int("Threads");


   ValueDraw = option_get_int("Contempt Factor");


   UseTB = option_get_bool("EGTB");
   TBDepth = option_get_int("EGTB Depth");
   TBpieceNb = tb_piece_nb();

   UseBB = option_get_bool("EGBB");
   BBDepth = option_get_int("EGBB Depth");
   BBpieceNb = egbb_piece_nb();


   list_note(list);
   list_sort(list);


   trans_move = MoveNone;
   if (UseTrans) trans_retrieve(board->key,&trans_move,&trans_min_depth,&trans_max_depth,&trans_min_value,&trans_max_value,&trans_eval,true);

   note_moves(list,board,0,trans_move,ThreadMain);
   list_sort(list);
}
