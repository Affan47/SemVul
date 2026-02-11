next_move() {
  Components cp(M);
#if VERBOSE >= 2
  cp.dump();
  _evaluate_board(curstate, 0, true);
#endif
  M(curstate.p[0]) = 1;
  M(curstate.p[1]) = 1;


  if(cp.component(curstate.p[0]) == cp.component(curstate.p[1])) {

    return next_move_alphabeta();
  } else {


    return next_move_spacefill(cp);
  }
}
