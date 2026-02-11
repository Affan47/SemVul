eval(CS& Cmd, const CARD_LIST* Scope)const
  {
    PARAMETER<double> x, y;
    Cmd >> x >> y;
    x.e_val(NOT_INPUT, Scope);
    y.e_val(NOT_INPUT, Scope);
    return to_string(std::max(x,y));
  }
