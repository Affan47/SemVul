move_is_en_passant(int move, const board_t * board) {

   ASSERT(move_is_ok(move));
   ASSERT(board_is_ok(board));

   return piece_is_pawn(move_piece(move,board))
       && move_to(move) == board->ep_square;
}
