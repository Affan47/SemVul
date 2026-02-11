add() {
    if ((U32)((t[cxt].c+256) >> 8-ch.bpos())==ch()) {
      if ((t[cxt].c >> 7-ch.bpos()) & 1)
        mixer.add(0, t[cxt].n);
      else
        mixer.add(t[cxt].n, 0);
    }
  }
