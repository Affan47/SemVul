sum(const IntArgs& args) {
    int i, sum = 0;
    const int size = args.size();

    for (i = 0 ; i < size ; ++i)
    {
      sum += args[i];
    }

    return LinIntExpr(sum);
  }
