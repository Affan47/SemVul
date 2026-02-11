init_between_bitboards() {
    SquareDelta step[8] = {
      DELTA_E, DELTA_W, DELTA_N, DELTA_S, DELTA_NE, DELTA_SW, DELTA_NW, DELTA_SE
    };
    SignedDirection d;
    for(Square s1 = SQ_A1; s1 <= SQ_H8; s1++)
      for(Square s2 = SQ_A1; s2 <= SQ_H8; s2++) {
        BetweenBB[s1][s2] = EmptyBoardBB;
        d = signed_direction_between_squares(s1, s2);
        if(d != SIGNED_DIR_NONE)
          for(Square s3 = s1 + step[d]; s3 != s2; s3 += step[d])
            set_bit(&(BetweenBB[s1][s2]), s3);
      }
  }
