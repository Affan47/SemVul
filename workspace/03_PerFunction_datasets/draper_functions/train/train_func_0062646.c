operator* (const Plane& pl1, const Plane& pl2)
  {
    if (pl1.malformed() || pl2.malformed())
      return Segment(true);


    P N3((pl1.perp())*(pl2.perp()));
    const double temp(norm(N3));

    if (temp < EPS)
      return Segment(true);


    N3 *= 1/temp;

    P perp((pl1.perp())*N3);
    P pt(pl1.pt() + (((pl2.pt()-pl1.pt())|pl2.perp())/(perp|pl2.perp()))*perp);
    P ctr(pt %= N3);


    return Segment(ctr - EPIX_INFTY*N3, ctr + EPIX_INFTY*N3);
  }
