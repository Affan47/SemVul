score_string(Value v) {
    std::stringstream s;

    if(abs(v) >= VALUE_MATE - 200) {
      if(v < 0)
        s << "-#" << (VALUE_MATE + v) / 2;
      else
        s << "#" << (VALUE_MATE - v + 1) / 2;
    }
    else {
      float floatScore = float(v) / float(PawnValueMidgame);
      if(v >= 0)
        s << '+';
      s << std::setprecision(2) << std::fixed << floatScore;
    }
    return s.str();
  }
