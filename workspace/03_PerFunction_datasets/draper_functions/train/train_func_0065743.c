prune<Set::SetView>(Space& home, Set::SetView x, int v) {
    return x.exclude(home, v);
  }
}}}
