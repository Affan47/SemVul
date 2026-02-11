jump(int spokes, int length, const std::vector<int>& seed)
  {
    P sum(P(0,0));

    for (int i=0; i< length; ++i)
      sum += cis(seed.at(i)*(full_turn())/spokes);

    return sum;
  }
