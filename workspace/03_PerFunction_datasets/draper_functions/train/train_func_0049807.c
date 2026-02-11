ponderhit() {
    int t = current_search_time();
    PonderSearch = false;
    if(Iteration >= 2 &&
       (!InfiniteSearch && (StopOnPonderhit ||
                            t > AbsoluteMaxSearchTime ||
                            (RootMoveNumber == 1 &&
                             t > MaxSearchTime + ExtraSearchTime) ||
                            (!FailHigh && !fail_high_ply_1() && !Problem &&
                             t > 6*(MaxSearchTime + ExtraSearchTime)))))
      AbortSearch = true;
  }
