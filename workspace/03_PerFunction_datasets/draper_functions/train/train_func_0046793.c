update_jumps(cell from, dir d)
  {
    if (not board_.on_board(from))
      return;

    int i = 1;
    cell p = from + d;

    while (board_.on_board(p) && board_.free(p))
    {
      p += d;
      i++;
    }
    if (not board_.on_board(p))
      return;

    cell to = p + d * i;
    if (free_between(p+d, to, d))
    {
      jump j(p, to, d);
      board_(from).jumps.push_back(j);
    }
  }
