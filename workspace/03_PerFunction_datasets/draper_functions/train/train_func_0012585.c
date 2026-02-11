operator()(unsigned a, unsigned b) const {
    return
      alns[a].qstrand != alns[b].qstrand ? alns[a].qstrand < alns[b].qstrand :
      alns[a].rname < alns[b].rname;
  }
