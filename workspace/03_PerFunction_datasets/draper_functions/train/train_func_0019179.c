gen_sliding_moves (int start_pos, int mod, int move_dir, int *moves_array)
{


    int i;
    for (i = 1; i < 8; i++) {
        int move = (move_dir * i) + start_pos;
        if ((square_on_board (move)) && (valid_x88_move (move) == TRUE)) {
            if (board[move] == chp_null) {
                moves_array[move] = TRUE;
            } else if (board[move] * mod > chp_null) {
                moves_array[move] = TRUE;
                break;
            } else {
                break;
            }
        } else {
            break;
        }
    }
}
