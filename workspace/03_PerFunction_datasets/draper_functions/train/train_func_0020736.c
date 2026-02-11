OrthogonalViewsFundamental(Mat3 *F) {
  Mat3 K1, R1, K2, R2;
  Vec3 t1, t2;
  Mat34 P1, P2;
  K1 << 1, 0, 0,
        0, 1, 0,
        0, 0, 1;
  K2 = K1;
  R1 << 1, 0, 0,
        0, 1, 0,
        0, 0, 1;
  R2 << 1, 0,  0,
        0, 0, -1,
        0, 1,  0;
  t1 << 0, 0, 0;
  t2 << -1, 1, 1;

  P_From_KRt(K1, R1, t1, &P1);
  P_From_KRt(K2, R2, t2, &P2);
  FundamentalFromProjections(P1, P2, F);
}
