update_pv(SearchStack ss[], int ply) {
    assert(ply >= 0 && ply < PLY_MAX);

    ss[ply].pv[ply] = ss[ply].currentMove;
    int p;
    for(p = ply + 1; ss[ply+1].pv[p] != MOVE_NONE; p++)
      ss[ply].pv[p] = ss[ply+1].pv[p];
    ss[ply].pv[p] = MOVE_NONE;
  }
